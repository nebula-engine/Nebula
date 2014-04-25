#include <stdio.h>

#include <math/xml.hpp>

#include <gru/material.hpp>
#include <gru/window/window.hpp>
#include <gru/scene/scene.hpp>





glutpp::material::raw::raw() {
	ambient_ = math::Color::black;
	diffuse_ = math::Color::cyan;
	specular_ = math::Color::white;
	emission_ = math::Color::black;
	shininess_ = 500;
}
void	glutpp::material::raw::load(tinyxml2::XMLElement* element) {
	
	if(element == NULL)
	{
		printf("no element\n");
		return;
	}
	
	ambient_  = math::Xml::parse_color<double>(element->FirstChildElement("ambient"), ambient_);
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

	p->get_uniform_scalar(glutpp::uniform_name::e::FRONT_AMBIENT)->load_4fv(raw_.ambient_);
	p->get_uniform_scalar(glutpp::uniform_name::e::FRONT_DIFFUSE)->load_4fv(raw_.diffuse_);
	p->get_uniform_scalar(glutpp::uniform_name::e::FRONT_SPECULAR)->load_4fv(raw_.specular_);
	p->get_uniform_scalar(glutpp::uniform_name::e::FRONT_EMISSION)->load_4fv(raw_.emission_);
	p->get_uniform_scalar(glutpp::uniform_name::e::FRONT_SHININESS)->load(raw_.shininess_);
}
void glutpp::material::material::step(double time) {
		
	//raw_.diffuse_.step(time);
}


