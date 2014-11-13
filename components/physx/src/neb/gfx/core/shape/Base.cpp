#include <glm/gtx/transform.hpp>

#include <gal/stl/map.hpp>

#include <gal/log/log.hpp>

#include <neb/core/util/debug.hpp>

#include <neb/gfx/util/io.hpp>
#include <neb/gfx/app/__gfx_glsl.hpp>
#include <neb/gfx/core/shape/base.hpp>
#include <neb/gfx/core/light/point.hpp>
#include <neb/gfx/core/light/spot.hpp>
#include <neb/gfx/core/light/directional.hpp>
#include <neb/gfx/glsl/attrib.hh>
#include <neb/gfx/glsl/uniform/scalar.hpp>
#include <neb/gfx/glsl/program/threed.hpp>
#include <neb/gfx/util/log.hpp>
#include <neb/gfx/mesh/tri1.hpp>
#include <neb/gfx/mesh/instanced.hpp>
#include <neb/gfx/opengl/uniform.hpp>

#include <neb/core/math/geo/polygon.hpp>

typedef neb::gfx::core::shape::base THIS;

neb::gfx::core::shape::base::base()
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;
}
neb::gfx::core::shape::base::~base() {}
void					neb::gfx::core::shape::base::init(neb::core::core::shape::util::parent * const & p)
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	setParent(p);

	if(!neb::core::app::__base::is_valid()) return;

	createMesh();
}
void					neb::gfx::core::shape::base::release()
{
	neb::core::core::shape::base::release();
}
void					neb::gfx::core::shape::base::step(gal::etc::timestep const & ts) {

	//material_front_.step(ts);
}
void					neb::gfx::core::shape::base::callbackPose(neb::core::pose const & gpose) {
	LOG(lg, neb::gfx::core::shape::sl, debug) << __PRETTY_FUNCTION__;
	LOG(lg, neb::gfx::core::shape::sl, debug) << gpose.mat4_cast();

	neb::core::core::shape::base::__callbackPose(gpose);

	if(mesh_slot_) {
		auto model = gpose.mat4_cast() * glm::scale(scale_);
		
		mesh_slot_->set<0>(model);
		LOG(lg, neb::gfx::core::shape::sl, debug) << "slot " << mesh_slot_->index_;
	}
}
void					neb::gfx::core::shape::base::setPose(neb::core::pose const & pose) {
	LOG(lg, neb::gfx::core::shape::sl, debug) << __PRETTY_FUNCTION__;
	
	auto npose = pose * pose_;

	neb::gfx::core::light::util::parent::setPose(npose);
}
void					neb::gfx::core::shape::base::draw(
		neb::gfx::glsl::program::base const * const & p,
		neb::core::pose const & pose)
{
	auto npose = pose * pose_;
	
	draw_elements(p, npose);
}
void			THIS::drawHF(
		neb::gfx::glsl::program::base const * const & p,
		neb::core::pose const & pose)
{
}
void			neb::gfx::core::shape::base::model_load(
		neb::gfx::glsl::program::base const * const & p,
		neb::core::pose const & pose)
{
	mat4 space = pose.mat4_cast() * glm::scale(scale_);

	neb::gfx::ogl::glUniform(
			p->uniform_table_[neb::gfx::glsl::uniforms::MODEL],
			space
			);
}
void			neb::gfx::core::shape::base::draw_elements(
		neb::gfx::glsl::program::base const * const & p,
		neb::core::pose const & pose)
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__ << " " << this;

	assert(p);

	if(mesh_)
	{
		mesh_->drawElements(p, pose, scale_);
	}
}
void			neb::gfx::core::shape::base::drawDebug(
		neb::gfx::glsl::program::base const * const & p,
		neb::core::pose const & pose)
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__ << " " << this;
	
	assert(p);
	
	if(mesh_)
	{
		mesh_->drawDebug(p, pose, scale_);
	}
}
std::weak_ptr<neb::core::core::light::base>		neb::gfx::core::shape::base::createLightPoint() {

	auto self(std::dynamic_pointer_cast<neb::core::core::shape::base>(shared_from_this()));

	typedef neb::gfx::core::light::point L;

	auto light = std::shared_ptr<L>(new L());

	neb::core::core::light::util::parent::insert(light);

	light->init(this);

	return light;
}
std::weak_ptr<neb::core::core::light::base>		neb::gfx::core::shape::base::createLightSpot(glm::vec3 d) {

	auto self(std::dynamic_pointer_cast<neb::core::core::shape::base>(shared_from_this()));

	typedef neb::gfx::core::light::spot L;

	auto light = std::shared_ptr<L>(new L(), gal::stl::deleter<L>());

	light->spot_direction_ = d;

	neb::core::core::light::util::parent::insert(light);

	light->init(this);

	return light;
}
std::weak_ptr<neb::core::core::light::base>		neb::gfx::core::shape::base::createLightDirectional(glm::vec3 d) {

	auto self(std::dynamic_pointer_cast<neb::core::core::shape::base>(shared_from_this()));

	typedef neb::gfx::core::light::directional L;
	
	auto light = std::shared_ptr<L>(new L(), gal::stl::deleter<L>());

	light->pose_.pos_ = d;

	neb::core::core::light::util::parent::insert(light);

	light->init(this);

	return light;
}
void						neb::gfx::core::shape::base::createMesh() {
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

}




