
#include <Nebula/Scene/Base.hh>

#include <Nebula/debug.hh>
#include <Nebula/Util/typedef.hpp>
#include <Nebula/Shape/Base.hh>

#include <Nebula/Actor/Actor/Base.hh>

neb::core::actor::actor::Base::Base() {
}
neb::core::actor::actor::Base::Base(sp::shared_ptr<neb::core::actor::Util::Parent> parent):
	neb::core::actor::Base(parent)
{
	NEBULA_ACTOR_BASE_FUNC;
}
void		neb::core::actor::actor::Base::init() {
	NEBULA_ACTOR_BASE_FUNC;

	neb::core::actor::Base::init();
}
void		neb::core::actor::actor::Base::set_pose(mat4 pose) {
	NEBULA_ACTOR_BASE_FUNC;

	neb::core::actor::Base::setPose(pose);
}
void		neb::core::actor::actor::Base::step(neb::core::TimeStep const & ts) {
	neb::core::actor::Base::step(ts);
}
void		neb::core::actor::actor::Base::release() {
	NEBULA_ACTOR_BASE_FUNC;
	
	neb::core::actor::Base::release();

}



