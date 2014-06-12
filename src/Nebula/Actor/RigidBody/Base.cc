#include <Galaxy-Log/log.hpp>

//#include <Nebula/Graphics/Context/Base.hh>
//#include <Nebula/Graphics/Camera/View/ridealong.hh>

//#include <Nebula/debug.hh>
//#include <Nebula/Types.hh>
//#include <Nebula/App/Base.hh>

//#include <Nebula/Actor/Util/Types.hh>
//#include <Nebula/Actor/Control/Util/Types.hh>

#include <Nebula/Actor/RigidBody/Base.hh>
//#include <Nebula/Actor/RigidDynamic/Local.hh>


neb::core::actor::RigidBody::Base::Base() {}
neb::core::actor::RigidBody::Base::Base(sp::shared_ptr<neb::core::actor::Util::Parent> parent):
	neb::core::actor::RigidActor::Base(parent)
{}
void		neb::core::actor::RigidBody::Base::init() {
	BOOST_LOG_CHANNEL_SEV(lg, "neb actor", debug) << __PRETTY_FUNCTION__;
	
	neb::core::actor::RigidActor::Base::init();
}
void		neb::core::actor::RigidBody::Base::release() {
	BOOST_LOG_CHANNEL_SEV(lg, "neb actor", debug) << __PRETTY_FUNCTION__;
	
	neb::core::actor::RigidActor::Base::release();
}
void		neb::core::actor::RigidBody::Base::step(neb::core::TimeStep const & ts) {
	neb::core::actor::RigidActor::Base::step(ts);
}



