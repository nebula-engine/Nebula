#include <Nebula/core/actor/RigidDynamic/Local.hh>

//neb::core::actor::rigiddynamic::local::local() {
//}
neb::core::actor::rigiddynamic::local::local(sp::shared_ptr<neb::core::actor::util::parent> parent):
	neb::core::actor::base(parent),
	neb::core::actor::actor::base(parent),
	neb::core::actor::rigidactor::base(parent),
	neb::core::actor::local(parent),
	neb::core::actor::actor::local(parent),
	neb::core::actor::rigidactor::local(parent),
	neb::core::actor::rigidbody::base(parent),
	neb::core::actor::rigidbody::local(parent),
	neb::core::actor::rigiddynamic::base(parent)
{
}
void				neb::core::actor::rigiddynamic::local::init() {
	neb::core::actor::rigidbody::local::init();
	neb::core::actor::rigiddynamic::base::init();
}
void				neb::core::actor::rigiddynamic::local::release() {
	neb::core::actor::rigidbody::local::release();
	neb::core::actor::rigiddynamic::base::release();
}
void				neb::core::actor::rigiddynamic::local::step(neb::core::TimeStep const & ts) {
	neb::core::actor::rigidbody::local::step(ts);
	neb::core::actor::rigiddynamic::base::step(ts);
}


