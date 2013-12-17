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
void	glutpp::material::init(std::shared_ptr<scene> scene)
{
	printf("%s\n",__PRETTY_FUNCTION__);

	scene_ = scene;
	
	uniforms_.ambient_.init(scene,"front.ambient");
	uniforms_.diffuse_.init(scene,"front.diffuse");
	uniforms_.specular_.init(scene,"front.specular");
	uniforms_.emission_.init(scene,"front.emission");
	uniforms_.shininess_.init(scene,"front.shininess");
}
void	glutpp::material::load()
{
	//printf("%s\n",__PRETTY_FUNCTION__);
	
	std::shared_ptr<scene> scene = scene_.lock();
	
	if(scene->all(glutpp::scene::SHADER))
	{
		uniforms_.ambient_.load_4fv(ambient_);
		uniforms_.diffuse_.load_4fv(diffuse_);
		uniforms_.specular_.load_4fv(specular_);
		uniforms_.emission_.load_4fv(emission_);
		uniforms_.shininess_.load_1f(shininess_);
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

