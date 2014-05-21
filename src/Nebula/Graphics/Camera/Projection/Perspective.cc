#include <stdio.h>
#include <assert.h>

#include <GL/glew.h>

//#include <galaxy/sig/connection.hpp>

//#include <math/quat.hpp>
//#include <math/mat44.hpp>

#include <Nebula/Math/Matrix.hh>
#include <Nebula/App/Base.hh>
#include <Nebula/Graphics/Window/Base.hh>
#include <Nebula/Scene/Base.hh>
#include <Nebula/Graphics/Camera/Projection/Perspective.hh>

Neb::Graphics::Camera::Projection::Base::Base(Neb::Graphics::Context::Base_s parent):
	parent_(parent)
{
}
void		Neb::Graphics::Camera::Projection::Base::load() {
	
	auto p = Neb::App::Base::globalBase()->get_program(Neb::program_name::e::LIGHT);
	
	glViewport(0, 0, getWindow()->w_, getWindow()->h_);
	
	p->get_uniform_scalar("proj")->load(proj());
}
std::shared_ptr<Neb::Graphics::Window::Base>		Neb::Graphics::Camera::Projection::Base::getWindow() {
	return parent_->parent_->isWindowBase();
}

Neb::Graphics::Camera::Projection::Perspective::Perspective(std::shared_ptr<Neb::Graphics::Context::Base> renderable):
	Neb::Graphics::Camera::Projection::Base(renderable),
	fovy_(45.0f),
	zn_(2.0f),
	zf_(10000.0f)
{

}
/*void		Neb::Graphics::Camera::Projection::Perspective::init(RENDERABLE_S renderable) {
	GLUTPP_DEBUG_0_FUNCTION;
	
	renderable_ = renderable;
}*/
physx::PxMat44	Neb::Graphics::Camera::Projection::Perspective::proj() {

	physx::PxMat44 ret = SetPerspective(fovy_, (float)getWindow()->w_/(float)getWindow()->h_, zn_, zf_);
	
	//ret.print();
	
	return ret;
}
void		Neb::Graphics::Camera::Projection::Perspective::step(double dt) {

}








