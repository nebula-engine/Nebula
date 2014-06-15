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


neb::core::actor::rigidbody::base::base(sp::shared_ptr<neb::core::actor::util::parent> parent):
	neb::core::actor::base(parent),
	neb::core::actor::actor::base(parent),
	neb::core::actor::rigidactor::base(parent)
{}
void		neb::core::actor::rigidbody::base::init() {
	BOOST_LOG_CHANNEL_SEV(lg, "neb actor", debug) << __PRETTY_FUNCTION__;
	
	neb::core::actor::rigidactor::base::init();
}
void		neb::core::actor::rigidbody::base::release() {
	BOOST_LOG_CHANNEL_SEV(lg, "neb actor", debug) << __PRETTY_FUNCTION__;
	
	neb::core::actor::rigidactor::base::release();
}
void		neb::core::actor::rigidbody::base::step(neb::core::TimeStep const & ts) {
	neb::core::actor::rigidactor::base::step(ts);
}



