#include <stdio.h>
#include <assert.h>

#include <GL/glew.h>

#include <galaxy/sig/connection.hpp>

#include <math/quat.hpp>
#include <math/mat44.hpp>

#include <gru/window/window.hpp>
#include <gru/scene/scene.hpp>
#include <gru/Camera/Projection/Perspective.hpp>

glutpp::Camera::Projection::Base::Base(std::shared_ptr<glutpp::renderable> renderable):
	renderable_(renderable)
{
}
void		glutpp::Camera::Projection::Base::load() {
	
	auto p = glutpp::master::Global()->get_program(glutpp::program_name::e::LIGHT);
	
	glViewport(0, 0, getWindow()->raw_.w_, getWindow()->raw_.h_);
	
	p->get_uniform_scalar("proj")->load(proj());
}
std::shared_ptr<glutpp::window::window>		glutpp::Camera::Projection::Base::getWindow() {
	assert(!renderable_.expired());
	auto r = renderable_.lock();
	
	return r->getWindow();
}

glutpp::Camera::Projection::Perspective::Perspective(std::shared_ptr<glutpp::renderable> renderable):
	glutpp::Camera::Projection::Base(renderable),
	fovy_(45.0f),
	zn_(2.0f),
	zf_(10000.0f)
{

}
/*void		glutpp::Camera::Projection::Perspective::init(RENDERABLE_S renderable) {
	GLUTPP_DEBUG_0_FUNCTION;
	
	renderable_ = renderable;
}*/
math::mat44<float>	glutpp::Camera::Projection::Perspective::proj() {
	math::mat44<float> ret;
	ret.SetPerspective(fovy_, (float)getWindow()->raw_.w_/(float)getWindow()->raw_.h_, zn_, zf_);
	
	ret.print();
	
	return ret;
}
void		glutpp::Camera::Projection::Perspective::step(double dt) {

}








