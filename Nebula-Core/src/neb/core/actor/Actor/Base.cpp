#include <gal/log/log.hpp>
#include <neb/core/scene/Base.hh>

#include <neb/debug.hh>
#include <neb/util/typedef.hpp>
#include <neb/core/shape/Base.hh>

#include <neb/core/actor/Actor/Base.hh>

//neb::core::actor::actor::base::base() {
//}
neb::core::actor::actor::base::base(sp::shared_ptr<neb::core::actor::util::parent> parent):
	neb::core::actor::base(parent)
{
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core actor", debug) << __PRETTY_FUNCTION__;
}
void		neb::core::actor::actor::base::init() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core actor", debug) << __PRETTY_FUNCTION__;

	neb::core::actor::base::init();
}
void		neb::core::actor::actor::base::setPose(neb::core::pose const & pose) {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core actor", debug) << __PRETTY_FUNCTION__;

	neb::core::actor::base::setPose(pose);
}
void		neb::core::actor::actor::base::step(gal::std::timestep const & ts) {
	neb::core::actor::base::step(ts);
}
/*void		neb::core::actor::actor::base::release() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core actor", debug) << __PRETTY_FUNCTION__;
	
	neb::core::actor::base::release();

}*/



