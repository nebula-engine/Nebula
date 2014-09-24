#include <glm/gtx/transform.hpp>

#include <gal/stl/map.hpp>

#include <gal/log/log.hpp>

#include <neb/core/math/geo/polygon.hpp>
#include <neb/core/util/config.hpp>
#include <neb/core/util/log.hpp>
#include <neb/core/util/debug.hpp>
#include <neb/core/core/shape/base.hpp>
#include <neb/core/core/light/base.hpp>

neb::core::core::shape::base::base(std::shared_ptr<neb::core::core::shape::util::parent> parent):
	parent_(parent),
	s_(1,1,1)
{
	LOG(lg, neb::core::core::shape::sl, debug) << __FUNCSIG__;
	assert(parent);
}
neb::core::core::shape::base::~base() {}
neb::core::pose				neb::core::core::shape::base::getPoseGlobal() {
	LOG(lg, neb::core::core::shape::sl, debug) << __FUNCSIG__;
	
	neb::core::pose m;
	
	auto parent = parent_.lock();
	if(parent) {
		m = parent->getPoseGlobal() * getPose();
	} else {
		m = getPose();
	}

	return m;
}
neb::core::pose				neb::core::core::shape::base::getPose() {
	return pose_;
}
void					neb::core::core::shape::base::init() {
	LOG(lg, neb::core::core::shape::sl, debug) << __FUNCSIG__;

	auto me = std::dynamic_pointer_cast<neb::core::core::shape::base>(shared_from_this());
	//auto scene = get_parent()->get_scene();

	// type

	// program
/*	if(image_.length() == 0) {
		program_ = neb::program_name::LIGHT;
	} else {
		** @todo replace this with something better... *
		//flag_.set(neb::core::core::shape::flag::e::IMAGE);

		program_ = neb::program_name::IMAGE;
	}
*/

	neb::core::core::shape::util::parent::init();
	neb::core::core::light::util::parent::init();

}
void					neb::core::core::shape::base::release() {
	LOG(lg, neb::core::core::shape::sl, debug) << __FUNCSIG__;

	//neb::util::parent<neb::core::core::shape::base>::release();
	neb::core::core::shape::util::parent::release();
	neb::core::core::light::util::parent::release();
}
void						neb::core::core::shape::base::step(
		gal::etc::timestep const & ts)
{
	neb::core::core::shape::util::parent::step(ts);
	neb::core::core::light::util::parent::step(ts);
}

