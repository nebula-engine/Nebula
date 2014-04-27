#include <stdio.h>

#include <math/xml.hpp>

#include <gru/material.hpp>
#include <gru/window/window.hpp>
#include <gru/scene/scene.hpp>





glutpp::material::raw::raw() {
	ambient_ = math::Color::black<float>();
	diffuse_ = math::Color::cyan<float>();
	specular_ = math::Color::white<float>();
	emission_ = math::Color::black<float>();
	shininess_ = 500;
}
void	glutpp::material::raw::load(tinyxml2::XMLElement* element) {
	
	if(element == NULL)
	{
		printf("no element\n");
		return;
	}
	
	ambient_  = math::Xml::parse_color<float>(element->FirstChildElement("ambient"), ambient_);
	diffuse_  = math::Xml::parse_color(element->FirstChildElement("diffuse"), diffuse_);
	specular_ = math::Xml::parse_color(element->FirstChildElement("specular"), specular_);
	emission_ = math::Xml::parse_color(element->FirstChildElement("emission"), emission_);
	
	shininess_ = math::Xml::parse_float<double>(element->FirstChildElement("shininess"), shininess_);

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


