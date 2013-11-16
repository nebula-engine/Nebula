
#include <NEB/Physics.h>
#include <NEB/Scene.h>
#include <NEB/Actor/Base.h>
#include <NEB/Actor/Rigid_Dynamic_Box.h>
#include <NEB/Actor/Rigid_Static_Plane.h>
#include <NEB/Actor/Light.h>

NEB::Scene::Scene():
	px_filter_shader_(NULL)
{
	actors_ = std::vector<NEB::Actor::Base*>();
}
NEB::Actor::Light* NEB::Scene::Create_Light()
{
	// create
	NEB::Actor::Light* actor = new NEB::Actor::Light;
	
	actors_.push_back(actor);
	
	return actor;
}
NEB::Actor::Rigid_Dynamic_Box*	NEB::Scene::Create_Rigid_Dynamic_Box()
{
 TiXmlElement* root = document.FirstChildElement( "Case" );
        if ( root )
        {
                TiXmlElement* element = root->FirstChildElement( "Parameter" );

                while ( element )
                {




	// create
	NEB::Actor::Rigid_Dynamic_Box* actor = new NEB::Actor::Rigid_Dynamic_Box;

	// PxMaterial
	physx::PxMaterial* px_mat = NEB::physics.px_physics_->createMaterial(1,1,1);

	
	physx::PxRigidDynamic* px_rigid_dynamic = NEB::physics.px_physics_->createRigidDynamic( actor->pose_ );

	
	if (!px_rigid_dynamic)
	{
		printf("create shape failed!");
		exit(1);
	}


	physx::PxBoxGeometry px_geometry( 1, 1, 1 );

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
NEB::Actor::Rigid_Static_Plane*	NEB::Scene::Create_Rigid_Static_Plane()
{
	// create
	NEB::Actor::Rigid_Static_Plane* actor = new NEB::Actor::Rigid_Static_Plane;

	// PxMaterial
	physx::PxMaterial* px_mat = NEB::physics.px_physics_->createMaterial(1,1,1);

	
	physx::PxRigidStatic* px_rigid_static = PxCreatePlane(*(NEB::physics.px_physics_), physx::PxPlane( physx::PxVec3(0.0f,1.0f,0.0f), 5.0f), *px_mat);
	
	if (!px_rigid_static)
	{
		printf("create shape failed!");
		exit(1);
	}
	
	// PxActor
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
	physx::PxU32 nbPxactor = px_scene_->getNbActors(physx::PxActorTypeSelectionFlag::eRIGID_DYNAMIC);

	// PxScene
	px_scene_->simulate(dt);
	px_scene_->fetchResults(true);

	// retrieve array of actors that moved
	physx::PxU32 nb_active_transforms;
	physx::PxActiveTransform* active_transforms = px_scene_->getActiveTransforms(nb_active_transforms);

	printf( "count PxRigidActor:%i count active transform:%i\n", nbPxactor, nb_active_transforms );

	// update each render object with the new transform
	for ( physx::PxU32 i = 0; i < nb_active_transforms; ++i )
	{
		physx::PxActor* px_actor = active_transforms[i].actor;

		printf( "actor type = %i\n", px_actor->getType() );

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

	for( auto it = actors_.begin(); it != actors_.end(); ++it )
	{
		actor = *it;
		if( actor )
		{
			actor->Display();
		}
	}
}	



