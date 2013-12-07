#include <stdio.h>
#include <assert.h>

#include <GL/glew.h>

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





