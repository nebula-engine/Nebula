#include <stdio.h>
#include <assert.h>

#include <GL/glew.h>

#include <galaxy/sig/connection.hpp>

#include <math/quat.hpp>
#include <math/mat44.hpp>

#include <gru/window/window.hpp>
#include <gru/scene/scene.hpp>
#include <gru/Camera/View/Base.hpp>



glutpp::Camera::View::Base::Base()
{

}
/*void		glutpp::Camera::View::Base::init(RENDERABLE_S renderable) {
	GLUTPP_DEBUG_0_FUNCTION;
	
	renderable_ = renderable;
}*/
/*math::mat44	glutpp::Camera::View::Base::view() {

	if(control_)
	{
		return control_->supply();
	}
	
	math::mat44 ret = math::lookat(
			math::vec3<double>(0.0, 0.0, 30.0),
			math::vec3<double>(0.0, 0.0, 0.0),
			math::vec3<double>(0.0, 1.0, 0.0));
	
	return ret;
}*/
void		glutpp::Camera::View::Base::load() {
	
	auto p = glutpp::master::Global()->get_program(glutpp::program_name::e::LIGHT);

	p->get_uniform(glutpp::uniform_name::e::VIEW)->load(view());
}








