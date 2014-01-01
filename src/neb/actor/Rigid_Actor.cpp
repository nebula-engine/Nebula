#include <neb/physics.h>
#include <neb/actor/Rigid_Actor.h>

void	neb::actor::Rigid_Actor::step_remote(double) {

}
void	neb::actor::Rigid_Actor::setupFiltering()
{
	assert(px_actor_);
	
	physx::PxRigidActor* actor = (physx::PxRigidActor*)px_actor_;
	
	physx::PxFilterData coll_data;
	coll_data.word0 = desc_.filter_data_.simulation_.word0; // word0 = own ID
	coll_data.word1 = desc_.filter_data_.simulation_.word1;  // word1 = ID mask to filter pairs that trigger a contact callback;
	coll_data.word2 = desc_.filter_data_.simulation_.word2;
	coll_data.word3 = desc_.filter_data_.simulation_.word3; // word0 = own ID
	
	physx::PxFilterData sq_data;
	sq_data.word0 = desc_.filter_data_.scene_query_.word0; // word0 = own ID
	sq_data.word1 = desc_.filter_data_.scene_query_.word1;  // word1 = ID mask to filter pairs that trigger a contact callback;
	sq_data.word2 = desc_.filter_data_.scene_query_.word2;
	sq_data.word3 = desc_.filter_data_.scene_query_.word3; // word0 = own ID


	const physx::PxU32 numShapes = actor->getNbShapes();
	
	physx::PxShape** shapes = new physx::PxShape*[numShapes];
	
	actor->getShapes(shapes, numShapes);

	for(physx::PxU32 i = 0; i < numShapes; i++)
	{
		physx::PxShape* shape = shapes[i];
		shape->setSimulationFilterData(coll_data);
		shape->setQueryFilterData(sq_data);
	}
	
	delete[] shapes;
}
neb::actor::desc	neb::actor::Rigid_Actor::get_projectile() {
	abort();
	neb::actor::desc desc;
	return desc;
}
neb::actor::desc	neb::actor::Rigid_Actor::get_desc() {

	return neb::actor::Actor::get_desc();
}
int			neb::actor::Rigid_Actor::create_shapes()
{
	physx::PxRigidActor* px_rigid_actor = static_cast<physx::PxRigidActor*>(px_actor_);
	
	physx::PxMaterial* px_mat = neb::__physics.px_physics_->createMaterial(1,1,1);
	
	std::shared_ptr<neb::shape> shape;
	
	for(unsigned int i = 0; i < desc_.num_shapes_; ++i)
	{
		shape.reset(new neb::shape);
		
		shape->desc_ = desc_.shapes_[i];
		shape->px_shape_ = px_rigid_actor->createShape( *(shape->to_geo()), *px_mat );
		
		shapes_.push_back(shape);
	}
	
	return 0;
}

