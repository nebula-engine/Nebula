#include <nebula/content/scene/admin/base.hpp>

#include <nebula/content/actor/admin/base.hpp>
#include <nebula/content/actor/admin/rigid_dynamic_box.hpp>
#include <nebula/content/actor/admin/rigid_static_plane.hpp>


#include <nebula/content/scene/physics/base.hpp>

n32200::base::base( std::shared_ptr<n32100::base> parent ):
	parent_( parent )
{

}
n32200::base::~base()
{

}
void				n32200::base::init()
{

}
void				n32200::base::shutdown()
{

}
void				n32200::base::update()
{

}
void				n32200::base::step( float dt )
{
	jess::scoped_ostream( &jess::cout, NEB_FUNCSIG );
	
	physx::PxU32 nbPxactor = px_scene_->getNbActors( physx::PxActorTypeSelectionFlag::eRIGID_DYNAMIC );
	jess::clog << "there are " << nbPxactor << " Pxrigid_actor objects in the scene" << std::endl;

	// PxScene
	px_scene_->simulate( dt );
	px_scene_->fetchResults(true);

	// retrieve array of actors that moved
	physx::PxU32			nb_active_transforms;
	physx::PxActiveTransform*	active_transforms = px_scene_->getActiveTransforms(nb_active_transforms);

	// update each render object with the new transform
	for ( physx::PxU32 i = 0; i < nb_active_transforms; ++i )
	{
		n34100::base* act = static_cast<n34100::base*>( active_transforms[i].userData );
		
		//NEB_ASSERT( act );
		if ( act )
		{
			physx::PxMat44 pose( active_transforms[i].actor2World );
			
			act->pose_ = pose;
		}
		//printf("transform.p.y=%16f\n",activeTransforms[i].actor2World.p.y);
	}
}
void				n32200::base::render( jess::shared_ptr<n23000::base> )
{

}
void				n32200::base::add( std::shared_ptr<n34100::rigid_dynamic_box> actor )
{
	std::shared_ptr<n34200::actor> physics = std::static_pointer_cast<n34200::actor>( actor->physics_ );

	px_scene_->addActor( *physics->px_actor_ );
	
	//jess::shared_ptr<n34200::rigid_dynamic_box> act( new n34200::rigid_dynamic_box() );
	
	//return act;
}
void				n32200::base::add( std::shared_ptr<n34100::rigid_static_plane> actor )
{
	std::shared_ptr<n34200::actor> physics = std::static_pointer_cast<n34200::actor>( actor->physics_ );

	px_scene_->addActor( *physics->px_actor_ );
	
	//jess::shared_ptr<n34200::rigid_dynamic_box> act( new n34200::rigid_dynamic_box() );
	
	//return act;
}

/*
jess::shared_ptr<n34200::controller>		n32200::base::create_controller()
{
	return ( parent_.lock()->create_physics_controller() );

	//jess::shared_ptr<n34200::controller> act( new n34200::controller() );
	
	//return act;
}*/
/*void				n32200::base::register_actor( jess::shared_ptr<n34100::actor> )
  {

  }*/
/*void	n32200::base::add_actor( jess::shared_ptr<n34100::actor> act )
  {
  jess::shared_ptr<n34200p::actor> pp_act = std::dynamic_pointer_cast<n34200p::actor>( act->physics_ );
  
  ::physx::PxActor* px_actor = pp_act->px_actor_;
  
  px_scene_->addActor(*px_actor);
  }*/
void	n32200::base::customize_scene_desc(::physx::PxSceneDesc& sceneDesc)
{
	sceneDesc.flags |= ::physx::PxSceneFlag::eENABLE_ACTIVETRANSFORMS;
}






