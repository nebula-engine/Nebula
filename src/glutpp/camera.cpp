#include <stdio.h>
#include <assert.h>

#include <GL/glew.h>

#include <sig/connection.h>

#include <math/quat.h>
#include <math/mat44.h>

#include <glutpp/window.h>
#include <glutpp/camera.h>

glutpp::camera::camera():
	window_(NULL),
	eye_(0.0f, 0.0f, 5.0f, 0.0f),
	center_(0.0f,0.0f,0.0f),
	up_(0.0f,1.0f,0.0f),
	fovy_(45.0f),
	zn_(2.0f),
	zf_(100.0f),
	w_(100),
	h_(100)
{

}
void		glutpp::camera::init(window* window)
{
	window_ = window;
	
	control_.init(window_);
}
int		glutpp::camera::north(float)
{
	return 1;
}
math::mat44	glutpp::camera::view()
{
	math::mat44 ret = math::lookat(eye_, center_, up_);

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
	assert(window_);

	glViewport(0, 0, w_, h_);

	if(window_->all(glutpp::window::SHADER))
	{
		window_->uniform_proj_.load_matrix4fv(proj());
		window_->uniform_view_.load_matrix4fv(view());
	}
	else
	{
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(proj());

		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(view());	
	}
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
	
	// look vector
	math::vec3 look = center_ - eye_;
	
	// project to xz-plane
	look.y = 0.0;
	look.normalize();
	
	math::vec3 x(1,0,0);
	math::vec3 y(0,1,0);
	math::vec3 z(0,0,-1);
	
	math::vec3 c = z.cross(look);
	
	float yaw = asin(c.magnitude());
	
	float d = y.dot(c);
	float e = z.dot(look);
	
	if(e < 0) yaw = M_PI - yaw;
	

	yaw *= (d > 0) ? 1.0 : -1.0;
	
	
	printf("yaw = %f\n",yaw);
	
	// rotate velocity by camera yaw
	math::quat q(yaw,y);
	
	
	math::vec3 v = control_.v0_ + control_.v1_;
	v *= dt;
	v *= 4.0;
		
	v = q.rotate(v);
	
	eye_ += math::vec4(v, 0.0f);
}










