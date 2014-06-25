#include <gal/log/log.hpp>

#include <neb/debug.hh>

//#include <neb/util/Typed.hh>

#include <neb/util/decl.hpp>
//#include <neb/config.hh> // Nebula/config.hpp.in
//#include <neb/timer/Actor/Base.hpp>
//#include <neb/app/Base.hh>
#include <neb/core/scene/Base.hh>
//#include <neb/gfx/window/util/signals.hpp>

#include <neb/core/actor/Base.hh>
#include <neb/core/actor/RigidActor/Base.hh>
#include <neb/core/actor/RigidBody/Base.hh>
#include <neb/core/actor/Empty/Empty.hpp>
#include <neb/core/actor/Util/Types.hh>

//#include <neb/gfx/window/Base.hh>
//#include <neb/gfx/util/decl.hpp>

/** @file Base
 */

//neb::core::actor::base::base() {
//}
neb::core::actor::base::base(sp::shared_ptr<neb::core::actor::util::parent> parent):
	density_(10.0),
	parent_(parent)
{
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core actor", debug) << __PRETTY_FUNCTION__;
}
neb::core::actor::base::~base() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core actor", debug) << __PRETTY_FUNCTION__;
}
void		neb::core::actor::base::init() {
}
sp::shared_ptr<neb::core::actor::util::parent>	neb::core::actor::base::get_parent() {
	auto parent(parent_.lock());
	assert(parent);
	return parent;
}
neb::core::pose				neb::core::actor::base::getPose() {
	return pose_;
}
neb::core::pose				neb::core::actor::base::getPoseGlobal() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core actor", debug) << __PRETTY_FUNCTION__;
	
	neb::core::pose p;
	
	auto parent(parent_.lock());
	
	if(!parent) {
		p = parent->getPoseGlobal() * getPose();
	} else {
		p = getPose();
	}

	return p;
}
void		neb::core::actor::base::setPose(neb::core::pose const & pose) {
	pose_ = pose;
	
	flag_.set(neb::core::actor::util::flag::E::SHOULD_UPDATE);
}
void		neb::core::actor::base::releaseUp() {
	
	gal::std::__release::release();
	
	neb::core::actor::util::parent::clear();
	neb::core::shape::util::parent::clear();

	//conn_.key_fun_.disconnect();
}
void		neb::core::actor::base::step(gal::std::timestep const & ts) {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core actor", debug) << __PRETTY_FUNCTION__;

	typedef neb::core::actor::util::parent A;
	typedef neb::core::shape::util::parent S;

	A::map_.for_each<0>([&] (A::map_type::iterator<0> it) {
			it->ptr_->step(ts);
			});

	S::map_.for_each<0>([&] (S::map_type::iterator<0> it) {
			it->ptr_->step(ts);
			});

}

