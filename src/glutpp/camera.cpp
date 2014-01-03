#include <stdio.h>
#include <assert.h>

#include <GL/glew.h>

#include <gal/sig/connection.h>

#include <math/quat.h>
#include <math/mat44.h>

#include <glutpp/window.h>
#include <glutpp/scene/scene.h>
#include <glutpp/camera.h>

glutpp::camera::camera():
	fovy_(45.0f),
	zn_(2.0f),
	zf_(100.0f),
	w_(100),
	h_(100)
{

}
void		glutpp::camera::init(std::shared_ptr<renderable> renderable)
{
	renderable_ = renderable;

	//control_.init(window_);
}
int		glutpp::camera::north(float)
{
	return 1;
}
math::mat44	glutpp::camera::view()
{
	if(control_)
	{
		return control_->supply();
	}


	math::mat44 ret = math::lookat(math::vec3(0.0, 0.0, 30.0), math::vec3(0.0, 0.0, 0.0), math::vec3(0.0, 1.0, 0.0));



	return ret;
}
math::mat44	glutpp::camera::proj()
{
	math::mat44 ret;

	ret.SetPerspective(fovy_, (float)w_/(float)h_, zn_, zf_);

	return ret;
}
void		glutpp::camera::load()
{
	auto p = glutpp::__master.get_program(glutpp::program_name::e::LIGHT);
	
	glViewport(0, 0, w_, h_);
	
	p->get_uniform(glutpp::uniform_name::e::PROJ)->load(proj());
	p->get_uniform(glutpp::uniform_name::e::VIEW)->load(view());
}
void		glutpp::camera::step(float dt)
{
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










