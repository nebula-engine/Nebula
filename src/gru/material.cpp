#include <stdio.h>

//#include <math/xml.hpp>

#include <gru/material.hpp>
#include <gru/window/window.hpp>
#include <gru/scene/scene.hpp>


gru::Color::color<float> operator<<(gru::Color::color<float> c, tinyxml2::XMLElement* element) {
	if(element != NULL) {
		char const * buf = element->GetText();
		
		sscanf(buf, "%f,%f,%f,%f", &c.r, &c.g, &c.b, &c.a);
	}
	
	return c;
}
float operator<<(float f, tinyxml2::XMLElement* element) {
	if(element != NULL) {
		char const * buf = element->GetText();
		
		sscanf(buf, "%f,%f,%f,%f", &c.r, &c.g, &c.b, &c.a);
	}
	
	return c;
}


glutpp::material::raw::raw() {
	ambient_ = gru::Color::black<float>();
	diffuse_ = gru::Color::cyan<float>();
	specular_ = gru::Color::white<float>();
	emission_ = gru::Color::black<float>();
	shininess_ = 500;
}
void	glutpp::material::raw::load(tinyxml2::XMLElement* element) {
	
	if(element == NULL)
	{
		printf("no element\n");
		return;
	}
	
	ambient_ << element->FirstChildElement("ambient");
	diffuse_  << element->FirstChildElement("diffuse");
	specular_ << element->FirstChildElement("specular");
	emission_ << element->FirstChildElement("emission");
	
	shininess_ << element->FirstChildElement("shininess");

	printf("diffuse = ");	
	diffuse_.print();
}




glutpp::material::material::material()
{}
void	glutpp::material::material::init()
{
	printf("%s\n",__PRETTY_FUNCTION__);
}

void	glutpp::material::material::load()
{
	auto p = glutpp::master::Global()->current_program();

	p->get_uniform_scalar("front.ambient")->load(raw_.ambient_);
	p->get_uniform_scalar("front.diffuse")->load(raw_.diffuse_);
	p->get_uniform_scalar("front.specular")->load(raw_.specular_);
	p->get_uniform_scalar("front.emission")->load(raw_.emission_);
	p->get_uniform_scalar("front.shininess")->load(raw_.shininess_);
}
void glutpp::material::material::step(double time) {
		
	//raw_.diffuse_.step(time);
}


