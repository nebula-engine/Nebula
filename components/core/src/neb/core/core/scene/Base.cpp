
#include <stdio.h>

#include <gal/log/log.hpp>

#include <neb/core/util/debug.hpp>
#include <neb/core/util/config.hpp>
#include <neb/core/util/log.hpp>
#include <neb/core/core/actor/base.hpp>
#include <neb/core/core/actor/util/decl.hpp>
#include <neb/core/core/light/base.hpp>
#include <neb/core/core/light/util/light_count.hpp>
#include <neb/core/core/shape/base.hpp>
#include <neb/core/core/scene/base.hpp>
#include <neb/core/core/scene/util/decl.hpp>
#include <neb/core/core/scene/util/parent.hpp>

using namespace std;

neb::core::core::scene::base::base(std::shared_ptr<neb::core::core::scene::util::parent> parent):
	parent_(parent)
{
	LOG(lg, neb::core::core::scene::sl, debug) << __FUNCSIG__;
}
neb::core::core::scene::base::~base() {
	LOG(lg, neb::core::core::scene::sl, debug) << __FUNCSIG__;
}
void neb::core::core::scene::base::init() {
	LOG(lg, neb::core::core::scene::sl, debug) << __FUNCSIG__;
}
void neb::core::core::scene::base::release() {
	LOG(lg, neb::core::core::scene::sl, debug) << __FUNCSIG__;
	
	neb::core::core::actor::util::parent::clear();
}
neb::core::pose						neb::core::core::scene::base::getPose() {
	return neb::core::pose();
}		
neb::core::pose						neb::core::core::scene::base::getPoseGlobal() {
	return neb::core::pose();
}
weak_ptr<neb::core::core::scene::util::parent>		neb::core::core::scene::base::getParent() {
	return parent_;
}
void						neb::core::core::scene::base::add_deferred(std::shared_ptr<neb::core::core::actor::base> actor) {

	actors_deferred_[actor->name_] = actor;
}
void		neb::core::core::scene::base::step(gal::etc::timestep const & ts) {

	typedef neb::core::core::actor::util::parent A;

	A::map_.for_each<0>([&] (A::map_type::iterator<0> it) {
			auto actor = std::dynamic_pointer_cast<neb::core::core::actor::base>(it->ptr_);
			assert(actor);
			actor->step(ts);
			});

}
weak_ptr<neb::core::core::actor::base>		neb::core::core::scene::base::createActorRigidStaticCube(
		neb::core::pose pose,
		double size) {

	auto actor = createActorRigidStaticUninitialized().lock();
	actor->pose_ = pose;
	actor->init();

	// create shape

	auto shape = actor->createShapeCube(neb::core::pose(), size);

	// reinitialize in order to apply filtering to shape
	/// @todo consider implementing refresh-type function instead
	actor->init();

	return actor;
}
weak_ptr<neb::core::core::actor::base>		neb::core::core::scene::base::createActorRigidDynamicCube(
		neb::core::pose pose,
		double size) {

	auto actor = createActorRigidDynamicUninitialized().lock();
	actor->pose_ = pose;
	actor->init();

	// shape
	auto shape = actor->createShapeCube(neb::core::pose(), size);

	/// @todo consider implementing refresh-type function instead
	actor->init();

	return actor;
}
weak_ptr<neb::core::core::actor::base>		neb::core::core::scene::base::createActorLightPoint(glm::vec3 p) {

	// actor
	auto actor = createActorBase(neb::core::pose(p)).lock();

	// shape	
	auto shape = actor->createShapeBase(neb::core::pose()).lock();

	// light
	auto light = shape->createLightPoint();

	return actor;	
}



