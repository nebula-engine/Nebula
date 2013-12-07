#include <stdio.h>

#include <glutpp/window.h>
#include <glutpp/material.h>

glutpp::material::material():
	ambient_(math::black),
	diffuse_(math::cyan),
	specular_(math::white),
	emission_(math::black),
	shininess_(128)
{}
void	glutpp::material::init(window* window)
{
	window_ = window;
	
	uniform_ambient_.init(window,"front.ambient");
	uniform_diffuse_.init(window,"front.diffuse");
	uniform_specular_.init(window,"front.specular");
	uniform_emission_.init(window,"front.emission");
	uniform_shininess_.init(window,"front.shininess");
}
void	glutpp::material::load()
{
	printf("%s\n",__PRETTY_FUNCTION__);
	
	if(window_->all(glutpp::window::SHADER))
	{
		uniform_ambient_.load_4fv(ambient_);
		uniform_diffuse_.load_4fv(diffuse_);
		uniform_specular_.load_4fv(specular_);
		uniform_emission_.load_4fv(emission_);
		uniform_shininess_.load_1f(shininess_);
	}
	else
	{
		glMaterialfv(GL_FRONT,GL_AMBIENT,ambient_);
		glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse_);
		glMaterialfv(GL_FRONT,GL_SPECULAR,specular_);
		glMaterialfv(GL_FRONT,GL_EMISSION,emission_);
		glMaterialf(GL_FRONT,GL_SHININESS,shininess_);
	}
}

