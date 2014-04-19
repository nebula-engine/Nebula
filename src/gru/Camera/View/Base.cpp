#include <stdio.h>
#include <assert.h>

#include <GL/glew.h>

#include <galaxy/sig/connection.hpp>

#include <math/quat.hpp>
#include <math/mat44.hpp>

#include <gru/window/window.hpp>
#include <gru/scene/scene.hpp>
#include <gru/Camera/View/Base.hpp>



glutpp::Camera::View::Base::Base():
	fovy_(45.0f),
	zn_(2.0f),
	zf_(10000.0f),
	w_(100),
	h_(100)
{

}
/*void		glutpp::Camera::View::Base::init(RENDERABLE_S renderable) {
	GLUTPP_DEBUG_0_FUNCTION;
	
	renderable_ = renderable;
}*/
int		glutpp::Camera::View::Base::north(float) {
	return 1;
}
math::mat44	glutpp::Camera::View::Base::view() {

	if(control_)
	{
		return control_->supply();
	}
	
	math::mat44 ret = math::lookat(
			math::vec3<double>(0.0, 0.0, 30.0),
			math::vec3<double>(0.0, 0.0, 0.0),
			math::vec3<double>(0.0, 1.0, 0.0));
	
	return ret;
}
math::mat44	glutpp::Camera::View::Base::proj() {
	math::mat44 ret;

	ret.SetPerspective(fovy_, (float)w_/(float)h_, zn_, zf_);

	return ret;
}
void		glutpp::Camera::View::Base::load() {
	
	auto p = glutpp::master::Global()->get_program(glutpp::program_name::e::LIGHT);

	glViewport(0, 0, w_, h_);

	p->get_uniform(glutpp::uniform_name::e::PROJ)->load(proj());
	p->get_uniform(glutpp::uniform_name::e::VIEW)->load(view());
}
void		glutpp::Camera::View::Base::step(float dt) {

	/*
	   for(auto it = connection_u_.begin(); it != connection_u_.end(); ++it)
	   {
	   v.x += std::get<0>((*it)->tup_);
	   }	
	   for(auto it = connection_v_.begin(); it != connection_v_.end(); ++it)
	   {
	   v.y += std::get<0>((*it)->tup_);
	   }
	   for(auto it = connection_w_.begin(); it != connection_w_.end(); ++it)
	   {
	   v.z += std::get<0>((*it)->tup_);
	   }
	 */
}








