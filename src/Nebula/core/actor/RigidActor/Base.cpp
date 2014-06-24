
#include <Nebula/debug.hh>
#include <Nebula/core/actor/RigidActor/Base.hh>
#include <Nebula/core/shape/Box.hh>

//neb::core::actor::rigidactor::base::base() {
//}
neb::core::actor::rigidactor::base::base(sp::shared_ptr<neb::core::actor::util::parent> parent):
	neb::core::actor::base(parent),
	neb::core::actor::actor::base(parent)
{
}
void		neb::core::actor::rigidactor::base::init() {
	neb::core::actor::actor::base::init();
}
/*void		neb::core::actor::rigidactor::base::release() {
	neb::core::actor::actor::base::release();
}*/
void		neb::core::actor::rigidactor::base::step(gal::std::timestep const & ts) {
	neb::core::actor::actor::base::step(ts);
}

sp::weak_ptr<neb::core::shape::box>		neb::core::actor::rigidactor::base::createShapeCube(real size) {
	
	auto shape = createShapeBoxUninitialized().lock();

	shape->s_ = vec3(size);

	shape->init();

	return shape;
	
}
sp::weak_ptr<neb::core::shape::box>		neb::core::actor::rigidactor::base::createShapeBoxUninitialized() {

	auto self(isActorRigidActor());

	auto shape = sp::make_shared<neb::core::shape::box>(self);
	
	neb::core::shape::util::parent::insert(shape);
	
	return shape;
}



