#include <Galaxy-Log/log.hpp>

//#include <neb/gfx/Context/Base.hh>
//#include <neb/gfx/Camera/View/ridealong.hh>

//#include <neb/debug.hh>
//#include <neb/util/decl.hpp>
//#include <neb/app/Base.hh>

//#include <neb/core/actor/Util/Types.hh>
//#include <neb/core/actor/Control/Util/Types.hh>
#include <neb/debug.hh>

#include <neb/core/actor/RigidBody/Base.hh>
//#include <neb/core/actor/RigidDynamic/Local.hh>


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



