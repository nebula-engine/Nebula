
#include <Nebula/Graphics/Context/Base.hh>
#include <Nebula/Scene/Base.hh>

#include <Nebula/debug.hh>
#include <Nebula/Util/typedef.hpp>
//#include <Nebula/simulation_callback.hh>
#include <Nebula/Shape/Base.hh>

#include <Nebula/Actor/Actor/Base.hh>

neb::Actor::Actor::Base::Base() {
}
neb::Actor::Actor::Base::Base(sp::shared_ptr<neb::Actor::Util::Parent> parent):
	neb::Actor::Base(parent)
{
	NEBULA_ACTOR_BASE_FUNC;
}
void		neb::Actor::Actor::Base::init() {
	NEBULA_ACTOR_BASE_FUNC;

	neb::Actor::Base::init();
}
void		neb::Actor::Actor::Base::set_pose(mat4 pose) {
	NEBULA_ACTOR_BASE_FUNC;

	neb::Actor::Base::setPose(pose);
}
int		neb::Actor::Actor::Base::fire() {
	NEBULA_ACTOR_BASE_FUNC;
	return neb::Actor::Base::fire();
}
void		neb::Actor::Actor::Base::step(neb::core::TimeStep const & ts) {
}


void		neb::Actor::Actor::Base::release() {
	NEBULA_ACTOR_BASE_FUNC;
	
	neb::Actor::Base::release();

	//assert(!scene_.expired());

}



