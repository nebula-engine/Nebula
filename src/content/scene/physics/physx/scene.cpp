#include <nebula/content/physics/physx/free.hpp>
#include <nebula/content/physics/physx/base.hpp>

#include <nebula/content/actor/admin/actor.hpp>
#include <nebula/content/actor/physics/physx/actor.hpp>

#include <nebula/content/scene/physics/physx/base.hpp>

#include <nebula/ns.hpp>

namespace bnu = boost::numeric::ublas;

void	nc_sc_pp::base::step(FLOAT dt)
{
	//::physx::PxU32 nbPxActor = px_scene_->getNbActors( physx::PxActorTypeSelectionFlag::eRIGID_DYNAMIC );
	//printf("there are %i PxRigidActor objects in the scene\n",nbPxActor);
	
	// PxScene
	px_scene_->simulate( dt );
	px_scene_->fetchResults(true);
	
	// retrieve array of actors that moved
	::physx::PxU32			nb_active_transforms;
	::physx::PxActiveTransform*	active_transforms = px_scene_->getActiveTransforms(nb_active_transforms);
	
	// update each render object with the new transform
	for ( ::physx::PxU32 i = 0; i < nb_active_transforms; ++i )
	{
		ncaa::base* act = static_cast<ncaa::base*>( active_transforms[i].userData );
		
		bnu::matrix<FLOAT> pose = ncpp::physx_to_boost( active_transforms[i].actor2World );
		
		act->set_pose( pose );
		
		//printf("transform.p.y=%16f\n",activeTransforms[i].actor2World.p.y);
	}
}
void	nc_sc_pp::base::add_actor(const boost::shared_ptr<ncaa::actor>& act)
{
	boost::shared_ptr<ncapp::actor> pp_act = boost::dynamic_pointer_cast<ncapp::base>( act->physics_.pointer_ );
	
	::physx::PxActor* px_actor = pp_act->px_actor_;
	
	scene_->add_actor(*pxActor);
}
void	nc_sc_pp::base::customize_scene_desc(::physx::PxSceneDesc& sceneDesc)
{
	sceneDesc.flags |= physx::PxSceneFlag::eENABLE_ACTIVETRANSFORMS;
}





