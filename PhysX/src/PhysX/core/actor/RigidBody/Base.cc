

#include <Nebula/Graphics/Context/Base.hh>
#include <Nebula/Graphics/Camera/View/ridealong.hh>

#include <Nebula/debug.hh>
#include <Nebula/Types.hh>
#include <Nebula/App/Base.hh>

#include <Nebula/Actor/Util/Types.hh>
//#include <Nebula/Actor/Control/Util/Types.hh>
#include <Nebula/Actor/RigidBody/Base.hh>
#include <Nebula/Actor/RigidDynamic/Local.hh>


neb::Actor::RigidBody::Base::Base() {}
neb::Actor::RigidBody::Base::Base(sp::shared_ptr<neb::Actor::Util::Parent> parent):
	neb::Actor::RigidActor::Base(parent),
	force_(0.0,0.0,0.0),
	torque_(0.0,0.0,0.0)
{}
void		neb::Actor::RigidBody::Base::init() {
	NEBULA_ACTOR_BASE_FUNC;
	
	neb::Actor::RigidActor::Base::init();
}
void		neb::Actor::RigidBody::Base::step(neb::core::TimeStep const & ts) {
	neb::Actor::RigidActor::Base::step(ts);
}



