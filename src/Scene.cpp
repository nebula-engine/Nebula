
#include <NEB/Physics.h>
#include <NEB/Scene.h>
#include <NEB/Actor/Base.h>

NEB::Scene::Scene()
{
	actors_ = std::vector<NEB::Actor::Base*>();
}
NEB::Actor::Rigid_Dynamic_Box*	NEB::Scene::Create_Rigid_Dynamic_Box()
{
	// create
	NEB::Actor::Rigid_Dynamic_Box* box = new NEB::Actor::Rigid_Dynamic_Box;
	
	// PxMaterial
	physx::PxMaterial* px_mat = NEB::physics.px_physics_->createMaterial(1,1,1);
	
	// PxActor
	physx::PxRigidDynamic* px_rigid_dynamic = NEB::physics.px_physics_->createRigidDynamic( physx::PxTransform( box->pose_ ) );

	box->px_actor_ = px_rigid_dynamic;
	// PxGeometry
	physx::PxBoxGeometry px_geometry( 1, 1, 1 );
	
	
	
	// PxShape
	box->px_shape_ = px_rigid_dynamic->createShape( px_geometry, *px_mat );
	
	// userData
	px_rigid_dynamic->userData = box;
	
	//printf("box=%p\n",box);
	
	actors_.push_back(box);
	
	// add PxActor to PxScene
	px_scene_->addActor(*px_rigid_dynamic);
	
	return box;
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



