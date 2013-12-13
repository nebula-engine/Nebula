

#include <neb/physics.h>
#include <neb/scene.h>
#include <neb/actor/Base.h>
#include <neb/actor/Rigid_Dynamic.h>
#include <neb/actor/Rigid_Static.h>
#include <neb/actor/Controller.h>
#include <neb/actor/Light.h>
#include <neb/shape.h>

int		parse_shape_type(char const * str)
{
	assert(str);
	if(strcmp(str,"box") == 0) return neb::shape::BOX;
	if(strcmp(str ,"sphere") == 0) return neb::shape::SPHERE;
	return neb::shape::NONE;
}
float		xml_parse_float(TiXmlElement* element)
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
math::quat 	xml_parse_quat(TiXmlElement* element)
{
	if( !element )
	{
		return math::quat(0.0f, math::vec3(0,0,0));
	}

	float x, y, z, w;

	char const * buf = element->GetText();

	int c = sscanf(buf, "%f,%f,%f,%f", &x, &y, &z, &w);
	assert(c==4);

	return math::quat(w, math::vec3(x,y,z));

}
math::vec3 	xml_parse_vec3(TiXmlElement* element)
{
	if( !element )
	{
		printf("element not found\n");
		exit(0);
		return math::vec3(0.0,0.0,0.0);
	}
	
	float x, y, z;
	
	char const * buf = element->GetText();
	
	int c = sscanf(buf, "%f,%f,%f", &x, &y, &z);
	assert(c==3);
	
	return math::vec3(x,y,z);
}
neb::shape*	xml_parse_geo(TiXmlElement* element)
{
	if(element == NULL) return NULL;
	
	int type = parse_shape_type(element->Attribute("type"));
	
	neb::shape* shape = NULL;
	
	switch(type)
	{
		case neb::shape::BOX:
			shape = new neb::box(element);
			break;
		case neb::shape::SPHERE:
			shape = new neb::sphere(element);
			break;
		default:
			break;
	}

	return shape;
}


neb::scene::scene():
	px_filter_shader_(NULL)
{

}
neb::actor::Light*			neb::scene::Create_Light(TiXmlElement* el_actor)
{
	printf("%s\n",__PRETTY_FUNCTION__);

	// create
	neb::actor::Light* actor = new neb::actor::Light;

	lights_.push_back(actor);

	return actor;
}
void					neb::scene::Create_Actors(TiXmlElement* el_scene)
{
	printf("%s\n",__PRETTY_FUNCTION__);

	TiXmlElement* el_actor = el_scene->FirstChildElement("actor");

	while( el_actor )
	{
		Create_Actor(el_actor);

		el_actor = el_actor->NextSiblingElement();
	}
}
void					neb::scene::Create_Actor(TiXmlElement* el_actor)
{
	printf("create actors\n");

	const char* buf = el_actor->Attribute("type");

	assert(buf);

	if( strcmp(buf, "rigid_dynamic") == 0)
	{
		Create_Rigid_Dynamic(el_actor);
	}
	else if( strcmp(buf, "rigid_static") == 0)
	{
		Create_Rigid_Static(el_actor);
	}	
	else if( strcmp(buf, "rigid_static_plane") == 0)
	{
		Create_Rigid_Static_Plane(el_actor);
	}	
	else if( strcmp(buf, "light") == 0)
	{
		Create_Light(el_actor);
	}
	else if( strcmp(buf, "controller") == 0)
	{
		Create_Controller(el_actor);
	}


}
neb::actor::Rigid_Dynamic*		neb::scene::Create_Rigid_Dynamic(TiXmlElement* el_actor)
{
	// create
	neb::actor::Rigid_Dynamic* actor = new neb::actor::Rigid_Dynamic;

	// inputs
	physx::PxVec3 position;
	physx::PxQuat orientation;

	// xml
	assert(el_actor);

	//	TiXmlElement* el_size = el_actor->FirstChildElement("size");
	//	TiXmlElement* el_velocity_lin = el_actor->FirstChildElement("velocity_linear");
	//	TiXmlElement* el_velocity_ang = el_actor->FirstChildElement("velocity_angular");

	math::vec3 p = xml_parse_vec3( el_actor->FirstChildElement("p"));
	math::quat q = xml_parse_quat(el_actor->FirstChildElement("q"));

	actor->pose_ = math::transform(p, q);

	// PxMaterial
	physx::PxMaterial* px_mat = neb::__physics.px_physics_->createMaterial(1,1,1);

	physx::PxRigidDynamic* px_rigid_dynamic =
		neb::__physics.px_physics_->createRigidDynamic( actor->pose_ );
	
	if (!px_rigid_dynamic)
	{
		printf("create shape failed!");
		exit(1);
	}

	// choose geometry
	neb::shape* shape = xml_parse_geo(el_actor->FirstChildElement("geo"));
	assert(shape);
	
	// PxShape
	actor->px_shape_ = px_rigid_dynamic->createShape( *(shape->geo_), *px_mat );
	
	// PxActor
	actor->px_actor_ = px_rigid_dynamic;

	// userData
	px_rigid_dynamic->userData = actor;

	//printf("box=%p\n",box);

	actors_.push(actor);

	// add PxActor to PxScene
	px_scene_->addActor(*px_rigid_dynamic);

	// init actor
	actor->shape_ = shape;
	actor->init();
	
	
	return actor;
}
neb::actor::Rigid_Static*		neb::scene::Create_Rigid_Static(TiXmlElement* el_actor)
{
	// create
	neb::actor::Rigid_Static* actor = new neb::actor::Rigid_Static;

	// inputs
	physx::PxVec3 position;
	physx::PxQuat orientation;

	// xml
	assert(el_actor);

	//	TiXmlElement* el_size = el_actor->FirstChildElement("size");
	//	TiXmlElement* el_velocity_lin = el_actor->FirstChildElement("velocity_linear");
	//	TiXmlElement* el_velocity_ang = el_actor->FirstChildElement("velocity_angular");

	math::vec3 p = xml_parse_vec3( el_actor->FirstChildElement("p"));
	math::quat q = xml_parse_quat(el_actor->FirstChildElement("q"));

	actor->pose_ = math::transform(p, q);

	// PxMaterial
	physx::PxMaterial* px_mat = neb::__physics.px_physics_->createMaterial(1,1,1);

	physx::PxRigidStatic* px_rigid_static =
		neb::__physics.px_physics_->createRigidStatic( actor->pose_ );
	
	if (!px_rigid_static)
	{
		printf("create actor failed!");
		exit(1);
	}
	
	// choose geometry
	neb::shape* shape = xml_parse_geo(el_actor->FirstChildElement("geo"));
	assert(shape);
	
	// PxShape
	actor->px_shape_ = px_rigid_static->createShape( *(shape->geo_), *px_mat );
	
	// PxActor
	actor->px_actor_ = px_rigid_static;
	
	// userData
	px_rigid_static->userData = actor;
	
	//printf("box=%p\n",box);
	
	actors_.push(actor);
	
	// add PxActor to PxScene
	px_scene_->addActor(*px_rigid_static);
	
	// init actor
	actor->shape_ = shape;
	actor->init();
	
	
	return actor;
}


neb::actor::Rigid_Static*		neb::scene::Create_Rigid_Static_Plane(TiXmlElement* el_actor)
{
	// create
	neb::actor::Rigid_Static* actor = new neb::actor::Rigid_Static;

	// xml
	math::vec3 n = xml_parse_vec3(el_actor->FirstChildElement("n"));
	float d = xml_parse_float(el_actor->FirstChildElement("d"));

	n.normalize();

	printf("n=%f,%f,%f\n", n.x, n.y, n.z);
	printf("d=%f\n", d);

	// PxMaterial
	physx::PxMaterial* px_mat = neb::__physics.px_physics_->createMaterial(1,1,1);

	// construct global pose for rendering
	//physx::PxQuat q(n.x, n.y, n.z, 0.0f);
	math::quat q(3.14f, math::vec3(1,0,0));


	math::transform pose(n * -1.0f * d, q);

	actor->pose_ = pose;

	printf("%f,%f,%f\n", pose.p.x, pose.p.y, pose.p.z);

	physx::PxPlane p(physx::PxVec3(n.x,n.y,n.z), d);

	// PxActor
	physx::PxRigidStatic* px_rigid_static = PxCreatePlane(*(neb::__physics.px_physics_), p, *px_mat);

	if (!px_rigid_static)
	{
		printf("create shape failed!");
		exit(1);
	}

	actor->px_actor_ = px_rigid_static;

	// userData
	px_rigid_static->userData = actor;

	//printf("box=%p\n",box);

	actors_.push(actor);

	// add PxActor to PxScene
	px_scene_->addActor(*px_rigid_static);

	return actor;
}
std::shared_ptr<neb::actor::Controller>	neb::scene::Create_Controller(TiXmlElement* el_actor)
{
	printf("%s\n",__FUNCTION__);

	//jess::scoped_ostream( &jess::clog, neb_FUNCSIG );
	math::vec3 p = xml_parse_vec3(el_actor->FirstChildElement("p"));	
	// create
	std::shared_ptr<neb::actor::Controller> actor(new neb::actor::Controller);

	physx::PxMaterial* px_mat = neb::__physics.px_physics_->createMaterial(1,1,1);

	// description 
	physx::PxExtendedVec3 position(p.x, p.y, p.z);

	physx::PxCapsuleControllerDesc desc;

	desc.position = position;
	desc.height = 1.0;
	desc.radius = 0.5;
	desc.scaleCoeff = 1.0;
	desc.volumeGrowth = 2.0;
	desc.density = 1000.0;
	desc.slopeLimit = 0.707;
	desc.stepOffset = 1.0;
	desc.contactOffset = 1.0;
	desc.material = px_mat;
	desc.climbingMode = physx::PxCapsuleClimbingMode::eEASY;
	desc.userData = actor.get();


	actor->px_controller_ = neb::__physics.px_character_controller_manager_->createController( *neb::__physics.px_physics_, px_scene_, desc );

	return actor;
}
void					neb::scene::step(double time)
{
	printf("%s\n",__PRETTY_FUNCTION__);
	
	double dt = time - last_;
	last_ = time;
	
	//physx::PxU32 nbPxactor = px_scene_->getNbActors(physx::PxActorTypeSelectionFlag::eRIGID_DYNAMIC);
	
	
	// forces
	printf("force\n");
	actors_.foreach(std::bind(&neb::actor::Base::add_force, std::placeholders::_1));
	printf("force 2\n");
	
	
	
	
	// PxScene
	px_scene_->simulate(dt);
	px_scene_->fetchResults(true);

	// retrieve array of actors that moved
	physx::PxU32 nb_active_transforms;
	physx::PxActiveTransform* active_transforms = px_scene_->getActiveTransforms(nb_active_transforms);

	//printf( "count PxRigidActor:%i count active transform:%i\n", nbPxactor, nb_active_transforms );

	//physx::PxTransform pose;
	math::transform pose;

	// update each render object with the new transform
	for ( physx::PxU32 i = 0; i < nb_active_transforms; ++i )
	{
		//physx::PxActor* px_actor = active_transforms[i].actor;

		//printf( "actor type = %i\n", px_actor->getType() );

		neb::actor::Base* actor = static_cast<neb::actor::Base*>( active_transforms[i].userData );

		//neb_ASSERT( act );
		if(actor != NULL)
		{
			pose = active_transforms[i].actor2World;
			actor->set_pose(pose);
		}
		//printf("transform.p.y=%16f\n",activeTransforms[i].actor2World.p.y);
	}
}



