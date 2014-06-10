
#include <Nebula/Scene/Base.hh>

#include <Nebula/debug.hh>
#include <Nebula/Util/typedef.hpp>
#include <Nebula/Shape/Base.hh>

#include <Nebula/Actor/Actor/Base.hh>

Neb::Actor::Actor::Base::Base() {
}
Neb::Actor::Actor::Base::Base(Neb::Actor::Util::Parent_s parent):
	Neb::Actor::Base(parent)
{
	NEBULA_ACTOR_BASE_FUNC;
}
void		Neb::Actor::Actor::Base::init() {
	NEBULA_ACTOR_BASE_FUNC;

	Neb::Actor::Base::init();
}
void		Neb::Actor::Actor::Base::set_pose(mat4 pose) {
	NEBULA_ACTOR_BASE_FUNC;

	Neb::Actor::Base::setPose(pose);
}
void		Neb::Actor::Actor::Base::step(Neb::Core::TimeStep const & ts) {
	Neb::Actor::Base::step(ts);
}
void		Neb::Actor::Actor::Base::release() {
	NEBULA_ACTOR_BASE_FUNC;
	
	Neb::Actor::Base::release();

}



