#include <stdio.h>

#include <glutpp/window.h>
#include <glutpp/scene.h>
#include <glutpp/material.h>

glutpp::material::material():
	ambient_(0.1,0.1,0.1,1.0),
	diffuse_(math::cyan),
	specular_(math::white),
	emission_(math::black),
	shininess_(1000)
{}
void	glutpp::material::init()
{
	printf("%s\n",__PRETTY_FUNCTION__);
}
void	glutpp::material::load_shader()
{
	auto p = glutpp::__master.current_program();

	p->get_uniform(glutpp::uniform_name::e::FRONT_AMBIENT)->load_4fv(ambient_);
	p->get_uniform(glutpp::uniform_name::e::FRONT_DIFFUSE)->load_4fv(diffuse_);
	p->get_uniform(glutpp::uniform_name::e::FRONT_SPECULAR)->load_4fv(specular_);
	p->get_uniform(glutpp::uniform_name::e::FRONT_EMISSION)->load_4fv(emission_);
	p->get_uniform(glutpp::uniform_name::e::FRONT_SHININESS)->load(shininess_);
}
void	glutpp::material::load_no_shader()
{

	glMaterialfv(GL_FRONT,GL_AMBIENT,ambient_);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse_);
	glMaterialfv(GL_FRONT,GL_SPECULAR,specular_);
	glMaterialfv(GL_FRONT,GL_EMISSION,emission_);
	glMaterialf(GL_FRONT,GL_SHININESS,shininess_);
}



