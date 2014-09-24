
#include <gal/log/log.hpp>

#include <neb/core/util/log.hpp>
#include <neb/core/util/config.hpp>
#include <neb/core/util/debug.hpp>
#include <neb/core/util/decl.hpp>
#include <neb/core/core/actor/base.hpp>
#include <neb/core/core/actor/util/decl.hpp>
#include <neb/core/core/scene/base.hpp>

/** @file base
 */

using namespace std;

neb::core::core::actor::base::base(std::shared_ptr<neb::core::core::actor::util::parent> parent):
	density_(10.0),
	parent_(parent)
{
	LOG(lg, neb::core::core::actor::sl, debug) << __FUNCSIG__;
	assert(parent);
}
neb::core::core::actor::base::~base() {
	LOG(lg, neb::core::core::actor::sl, debug) << __FUNCSIG__;
}
void		neb::core::core::actor::base::init() {
}
void		neb::core::core::actor::base::release() {
	
	gal::itf::__release::release();
	
	neb::core::core::actor::util::parent::clear();
	neb::core::core::shape::util::parent::clear();

}
std::shared_ptr<neb::core::core::actor::util::parent>	neb::core::core::actor::base::get_parent() {
	auto parent(parent_.lock());
	assert(parent);
	return parent;
}
neb::core::pose				neb::core::core::actor::base::getPose() {
	return pose_;
}
neb::core::pose				neb::core::core::actor::base::getPoseGlobal() {
	LOG(lg, neb::core::core::actor::sl, debug) << __FUNCSIG__;
	
	neb::core::pose p;
	
	auto parent(parent_.lock());
	
	if(!parent) {
		p = parent->getPoseGlobal() * getPose();
	} else {
		p = getPose();
	}

	return p;
}
void		neb::core::core::actor::base::setPose(neb::core::pose const & pose) {
	pose_ = pose;
	
	neb::core::core::shape::util::parent::callbackPose(pose);
	
	flag_.set(neb::core::core::actor::util::flag::E::SHOULD_UPDATE);
}
void		neb::core::core::actor::base::step(gal::etc::timestep const & ts) {
	LOG(lg, neb::core::core::actor::sl, debug) << __FUNCSIG__;

	typedef neb::core::core::actor::util::parent A;
	typedef neb::core::core::shape::util::parent S;

	A::map_.for_each<0>([&] (A::map_type::iterator<0> it) {
			it->ptr_->step(ts);
			});

	S::map_.for_each<0>([&] (S::map_type::iterator<0> it) {
			it->ptr_->step(ts);
			});

}
weak_ptr<neb::core::core::shape::base>		neb::core::core::actor::base::createShapeCube(
		neb::core::pose pose, double size) {
	
	auto shape = createShapeBox(pose, glm::vec3(size));

	return shape;
	
}










