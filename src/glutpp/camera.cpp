#include <stdio.h>
#include <glutpp/camera.h>

glutpp::camera::camera():
	eye_(0.0f, 0.0f, 5.0f, 0.0f),
	center_(0.0f,0.0f,0.0f),
	up_(0.0f,1.0f,0.0f),
	fovy_(65.0f),
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

