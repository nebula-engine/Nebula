#include <glm/gtx/transform.hpp>

#include <Galaxy-Standard/map.hpp>
#include <Galaxy-Log/log.hpp>

#include <neb/debug.hh>
//#include <neb/app/Base.hh>
#include <neb/core/shape/Base.hh>

#include <neb/core/light/Base.hh>
//#include <neb/gfx/glsl/attrib.hh>
//#include <neb/gfx/glsl/Uniform/scalar.hpp>
#include <neb/math/geo/polygon.hpp>

neb::core::shape::base::base(sp::shared_ptr<neb::core::shape::util::parent> parent):
	parent_(parent),
	s_(1,1,1)
{
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core shape", debug) << __PRETTY_FUNCTION__;
	assert(parent);
}
neb::core::shape::base::~base() {}
neb::core::pose				neb::core::shape::base::getPoseGlobal() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core shape", debug) << __PRETTY_FUNCTION__;
	
	neb::core::pose m;
	
	auto parent = parent_.lock();
	if(parent) {
		m = parent->getPoseGlobal() * getPose();
	} else {
		m = getPose();
	}

	return m;
}
neb::core::pose				neb::core::shape::base::getPose() {
	return pose_;
}
void					neb::core::shape::base::init() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core shape", debug) << __PRETTY_FUNCTION__;

	auto me = sp::dynamic_pointer_cast<neb::core::shape::base>(shared_from_this());
	//auto scene = get_parent()->get_scene();

	// type

	// program
/*	if(image_.length() == 0) {
		program_ = neb::program_name::LIGHT;
	} else {
		** @todo replace this with something better... *
		//flag_.set(neb::core::shape::flag::e::IMAGE);

		program_ = neb::program_name::IMAGE;
	}
*/

	neb::core::shape::util::parent::init();
	neb::Light::util::parent::init();

	createMesh();
}
void					neb::core::shape::base::release() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core shape", debug) << __PRETTY_FUNCTION__;

	//neb::util::parent<neb::core::shape::base>::release();
	neb::core::shape::util::parent::release();
	neb::Light::util::parent::release();
}
void					neb::core::shape::base::step(gal::std::timestep const & ts) {

	neb::core::shape::util::parent::step(ts);

	neb::Light::util::parent::step(ts);

	material_front_.step(ts);
}


