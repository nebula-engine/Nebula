#include <stdio.h>
#include <assert.h>
#include <iomanip>

#include <GL/glew.h>

#include <gal/log/log.hpp>

//#include <math/quat.hpp>
//#include <math/mat44.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include <neb/core/util/debug.hpp>
#include <neb/core/core/actor/base.hpp>

#include <neb/phx/test.hpp>

#include <neb/gfx/camera/proj/perspective.hpp>
#include <neb/gfx/environ/base.hpp>
#include <neb/gfx/glsl/uniform/scalar.hpp>
#include <neb/gfx/glsl/program/base.hpp>
#include <neb/gfx/util/log.hpp>
#include <neb/gfx/util/io.hpp>
#include <neb/gfx/opengl/uniform.hpp>

neb::gfx::camera::proj::base::base(std::shared_ptr<neb::gfx::environ::base> parent):
	parent_(parent)
{
}
void		neb::gfx::camera::proj::base::load(neb::gfx::glsl::program::base const * const p) {
	
	//glViewport(0, 0, parent_->viewport_.w_, parent_->viewport_.h_);
	
	neb::gfx::ogl::glUniform(
			p->uniform_table_[neb::gfx::glsl::uniforms::PROJ],
			_M_matrix);
}
void		neb::gfx::camera::proj::base::step(gal::etc::timestep const & ts) {

}
void		neb::gfx::camera::proj::base::calculate_geometry()
{
	_M_px_geometry = neb::frustrum_geometry(_M_matrix);
}

neb::gfx::camera::proj::perspective::perspective(std::shared_ptr<neb::gfx::environ::base> parent):
	neb::gfx::camera::proj::base(parent),
	fovy_(45.0f),
	zn_(2.0f),
	zf_(1000.0f)
{
	calculate();
}
/*void		neb::gfx::camera::proj::perspective::init(RENDERABLE_S renderable) {
	GLUTPP_DEBUG_0_FUNCTION;
	
	renderable_ = renderable;
}*/
glm::mat4&		neb::gfx::camera::proj::perspective::proj() {
	return _M_matrix;
}
void		neb::gfx::camera::proj::perspective::set(float fovy, float near, float far)
{
	fovy_ = fovy;
	zn_ = near;
	zf_ = far;
	calculate();
}
void		neb::gfx::camera::proj::perspective::calculate() {

	auto parent = parent_.lock();
	assert(parent);

	LOG(lg, neb::gfx::sl, debug) << ::std::setw(8) << "fovy" << ::std::setw(8) << fovy_;
	LOG(lg, neb::gfx::sl, debug) << ::std::setw(8) << "aspect" << ::std::setw(8) << parent->viewport_.aspect_;
	LOG(lg, neb::gfx::sl, debug) << ::std::setw(8) << "zn" << ::std::setw(8) << zn_;
	LOG(lg, neb::gfx::sl, debug) << ::std::setw(8) << "zf" << ::std::setw(8) << zf_;
	

	if(parent->viewport_.aspect_ == 0.0) {
		parent->viewport_.aspect_ = 1.0;
	}

	_M_matrix = glm::perspective(fovy_, parent->viewport_.aspect_, zn_, zf_);

	calculate_geometry();
}
void		neb::gfx::camera::proj::perspective::step(gal::etc::timestep const & ts) {

}








