
#include <NEB/Physics.h>
#include <NEB/Scene.h>
#include <NEB/Actor/Base.h>

NEB::Scene::Scene()
{
	actors_ = std::vector<NEB::Actor::Base*>();
}
NEB::Actor::Rigid_Dynamic_Box*	NEB::Scene::Create_Rigid_Dynamic_Box()
{
	//jess::clog << NEB_FUNCSIG << std::endl;

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
	
	printf("box=%p\n",box);
	
	actors_.push_back( box );

	return box;
}
void				NEB::Scene::Display()
{
	NEB::Actor::Base* actor = NULL;

	printf("len(actos_)=%i\n", (int)actors_.size());

	for( auto it = actors_.begin(); it != actors_.end(); ++it )
	{
		actor = *it;
		if( actor )
		{
			actor->Display();
		}
	}
}	



