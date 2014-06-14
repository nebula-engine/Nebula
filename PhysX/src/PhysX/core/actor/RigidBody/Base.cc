

#include <Nebula/Graphics/Context/Base.hh>
#include <Nebula/Graphics/Camera/View/ridealong.hh>

#include <Nebula/debug.hh>
#include <Nebula/Types.hh>
#include <Nebula/App/Base.hh>

#include <Nebula/Actor/Util/Types.hh>
//#include <Nebula/Actor/Control/Util/Types.hh>
#include <Nebula/Actor/RigidBody/Base.hh>
#include <Nebula/Actor/RigidDynamic/Local.hh>


neb::core::actor::RigidBody::Base::Base() {}
neb::core::actor::RigidBody::Base::Base(sp::shared_ptr<neb::core::actor::Util::Parent> parent):
	neb::core::actor::RigidActor::Base(parent),
	force_(0.0,0.0,0.0),
	torque_(0.0,0.0,0.0)
{}
void		neb::core::actor::RigidBody::Base::init() {
	NEBULA_ACTOR_BASE_FUNC;
	
	neb::core::actor::RigidActor::Base::init();
}
void		neb::core::actor::RigidBody::Base::step(neb::core::TimeStep const & ts) {
	neb::core::actor::RigidActor::Base::step(ts);
}



