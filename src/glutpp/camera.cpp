#include <stdio.h>
#include <GL/gl.h>

#include <glutpp/camera.h>

glutpp::camera::camera():
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
math::mat44	glutpp::camera::view()
{
	//eye_.print();
	//center_.print();
	//up_.print();
	
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
	glViewport(0, 0, w_, h_);
	
	//proj.print();
	//view.print();

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(proj());
	//glLoadIdentity();
	//gluPerspective(65.0f, (float)width/(float)height, 2.0f, 50.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(view());	
}
