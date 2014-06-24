#include <Galaxy-Log/log.hpp>

//#include <Nebula/gfx/Context/Base.hh>
//#include <Nebula/gfx/Camera/View/ridealong.hh>

//#include <Nebula/debug.hh>
//#include <Nebula/util/decl.hpp>
//#include <Nebula/app/Base.hh>

//#include <Nebula/core/actor/Util/Types.hh>
//#include <Nebula/core/actor/Control/Util/Types.hh>
#include <Nebula/debug.hh>

#include <Nebula/core/actor/RigidBody/Base.hh>
//#include <Nebula/core/actor/RigidDynamic/Local.hh>


neb::core::actor::rigidbody::base::base(sp::shared_ptr<neb::core::actor::util::parent> parent):
	neb::core::actor::base(parent),
	neb::core::actor::actor::base(parent),
	neb::core::actor::rigidactor::base(parent)
{}
void		neb::core::actor::rigidbody::base::init() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb actor", debug) << __PRETTY_FUNCTION__;
	
	neb::core::actor::rigidactor::base::init();
}
/*void		neb::core::actor::rigidbody::base::release() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb actor", debug) << __PRETTY_FUNCTION__;
	
	neb::core::actor::rigidactor::base::release();
}*/
void		neb::core::actor::rigidbody::base::step(gal::std::timestep const & ts) {
	neb::core::actor::rigidactor::base::step(ts);
}



