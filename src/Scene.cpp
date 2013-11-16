

#include <NEB/Physics.h>
#include <NEB/Scene.h>
#include <NEB/Actor/Base.h>
#include <NEB/Actor/Rigid_Dynamic_Box.h>
#include <NEB/Actor/Rigid_Static_Plane.h>
#include <NEB/Actor/Light.h>

float xml_parse_float(TiXmlElement* element)
{
	if( !element )
	{
		return 0.0f;
	}
	
	float f;
	
	char const * buf = element->GetText();
	
	int c = sscanf(buf, "%f", &f);
	assert(c==1);
	
	return f;
}
physx::PxQuat xml_parse_quat(TiXmlElement* element)
{
	if( !element )
	{
		return physx::PxQuat(0.0f, physx::PxVec3(0,0,0));
	}
	
	float x, y, z, w;
	
	char const * buf = element->GetText();
	
	int c = sscanf(buf, "%f,%f,%f,%f", &x, &y, &z, &w);
	assert(c==4);
	
	return physx::PxQuat(w, physx::PxVec3(x,y,z));

}
physx::PxVec3 xml_parse_vec3(TiXmlElement* element)
{
	if( !element )
	{
		return physx::PxVec3(0,0,0);
	}
	
	float x, y, z;
	
	char const * buf = element->GetText();
	
	int c = sscanf(buf, "%f,%f,%f", &x, &y, &z);
	assert(c==3);
	
	return physx::PxVec3(x,y,z);
}

NEB::Scene::Scene():
	px_filter_shader_(NULL)
{

}
NEB::Actor::Light* NEB::Scene::Create_Light(TiXmlElement* el_actor)
{
	// create
	NEB::Actor::Light* actor = new NEB::Actor::Light;
	
	lights_.push_back(actor);
	
	return actor;
}
void	NEB::Scene::Create_Actors(TiXmlElement* el_scene)
{
	TiXmlElement* el_actor = el_scene->FirstChildElement("actor");
	
	while( el_actor )
	{
		Create_Actor(el_actor);
		
		el_actor = el_actor->NextSiblingElement();
	}
}
void	NEB::Scene::Create_Actor(TiXmlElement* el_actor)
{
	const char* buf = el_actor->Attribute("type");
	
	assert(buf);
	
	if( strcmp(buf, "rigid_dynamic_box") == 0)
	{
		Create_Rigid_Dynamic_Box(el_actor);
	}
	else if( strcmp(buf, "rigid_static_plane") == 0)
	{
		Create_Rigid_Static_Plane(el_actor);
	}	
	else if( strcmp(buf, "light") == 0)
	{
		Create_Light(el_actor);
	}

}
NEB::Actor::Rigid_Dynamic_Box*	NEB::Scene::Create_Rigid_Dynamic_Box(TiXmlElement* el_actor)
{
	// create
	NEB::Actor::Rigid_Dynamic_Box* actor = new NEB::Actor::Rigid_Dynamic_Box;

	// inputs
	physx::PxVec3 position;
	physx::PxQuat orientation;
	
	// xml
	assert(el_actor);
	
//	TiXmlElement* el_size = el_actor->FirstChildElement("size");
//	TiXmlElement* el_velocity_lin = el_actor->FirstChildElement("velocity_linear");
//	TiXmlElement* el_velocity_ang = el_actor->FirstChildElement("velocity_angular");
	
	physx::PxVec3 p = xml_parse_vec3( el_actor->FirstChildElement("p"));
	physx::PxQuat q = xml_parse_quat(el_actor->FirstChildElement("q"));
	
	actor->pose_ = physx::PxTransform(p, q);
	
	// PxMaterial
	physx::PxMaterial* px_mat = NEB::physics.px_physics_->createMaterial(1,1,1);


	physx::PxRigidDynamic* px_rigid_dynamic = NEB::physics.px_physics_->createRigidDynamic( actor->pose_ );

	if (!px_rigid_dynamic)
	{
		printf("create shape failed!");
		exit(1);
	}
	
	physx::PxBoxGeometry px_geometry(1, 1, 1);

	// PxShape
	actor->px_shape_ = px_rigid_dynamic->createShape( px_geometry, *px_mat );

	// PxActor
	actor->px_actor_ = px_rigid_dynamic;

	// userData
	px_rigid_dynamic->userData = actor;

	//printf("box=%p\n",box);

	actors_.push_back(actor);

	// add PxActor to PxScene
	px_scene_->addActor(*px_rigid_dynamic);

	return actor;
}
NEB::Actor::Rigid_Static_Plane*	NEB::Scene::Create_Rigid_Static_Plane(TiXmlElement* el_actor)
{
	// create
	NEB::Actor::Rigid_Static_Plane* actor = new NEB::Actor::Rigid_Static_Plane;

	// xml
	physx::PxVec3 n = xml_parse_vec3(el_actor->FirstChildElement("n"));
	float d = xml_parse_float(el_actor->FirstChildElement("d"));
	
	n.normalize();

	printf("n=%f,%f,%f\n", n.x, n.y, n.z);
	printf("d=%f\n", d);

	// PxMaterial
	physx::PxMaterial* px_mat = NEB::physics.px_physics_->createMaterial(1,1,1);
	
	physx::PxQuat q(n.x, n.y, n.z, 0.0f);
	
	physx::PxTransform pose(n * -1.0f * d, q);
	
	actor->pose_ = pose;
	
	printf("%f,%f,%f\n", pose.p.x, pose.p.y, pose.p.z);
	
	// PxActor
	physx::PxRigidStatic* px_rigid_static = PxCreatePlane(*(NEB::physics.px_physics_), physx::PxPlane(n, d), *px_mat);
	
	if (!px_rigid_static)
	{
		printf("create shape failed!");
		exit(1);
	}
	
	actor->px_actor_ = px_rigid_static;

	// userData
	px_rigid_static->userData = actor;

	//printf("box=%p\n",box);

	actors_.push_back(actor);

	// add PxActor to PxScene
	px_scene_->addActor(*px_rigid_static);

	return actor;
}

void NEB::Scene::Step(float dt)
{
	//physx::PxU32 nbPxactor = px_scene_->getNbActors(physx::PxActorTypeSelectionFlag::eRIGID_DYNAMIC);

	// PxScene
	px_scene_->simulate(dt);
	px_scene_->fetchResults(true);

	// retrieve array of actors that moved
	physx::PxU32 nb_active_transforms;
	physx::PxActiveTransform* active_transforms = px_scene_->getActiveTransforms(nb_active_transforms);

	//printf( "count PxRigidActor:%i count active transform:%i\n", nbPxactor, nb_active_transforms );

	// update each render object with the new transform
	for ( physx::PxU32 i = 0; i < nb_active_transforms; ++i )
	{
		//physx::PxActor* px_actor = active_transforms[i].actor;

		//printf( "actor type = %i\n", px_actor->getType() );

		NEB::Actor::Base* actor = static_cast<NEB::Actor::Base*>( active_transforms[i].userData );

		//NEB_ASSERT( act );
		if ( actor )
		{
			actor->pose_ = active_transforms[i].actor2World;
		}
		//printf("transform.p.y=%16f\n",activeTransforms[i].actor2World.p.y);
	}

}
void				NEB::Scene::Display()
{
	if( px_scene_ )
	{
		Step(1.0f/60.0f);
	}

	NEB::Actor::Base* actor = NULL;

	//printf("len(actos_)=%i\n", (int)actors_.size());
	for( auto it = lights_.begin(); it != lights_.end(); ++it )
	{
		actor = *it;
		if( actor )
		{
			actor->Display();
		}
	}

	for( auto it = actors_.begin(); it != actors_.end(); ++it )
	{
		actor = *it;
		if( actor )
		{
			actor->Display();
		}
	}
}	



