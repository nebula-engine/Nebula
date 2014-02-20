#include <stdio.h>

#include <math/free.h>

#include <glutpp/window/window.h>
#include <glutpp/scene/scene.h>
#include <glutpp/material.h>




glutpp::material::raw::raw() {
	ambient_ = math::black;
	diffuse_ = math::cyan;
	specular_ = math::white;
	emission_ = math::black;
	shininess_ = 500;
}
void	glutpp::material::raw::load(tinyxml2::XMLElement* element) {
	
	if(element == NULL)
	{
		printf("no element\n");
		return;
	}
	
	ambient_  = math::xml_parse_color(element->FirstChildElement("ambient"), ambient_);
	diffuse_  = math::xml_parse_color(element->FirstChildElement("diffuse"), diffuse_);
	specular_ = math::xml_parse_color(element->FirstChildElement("specular"), specular_);
	emission_ = math::xml_parse_color(element->FirstChildElement("emission"), emission_);
	
	shininess_ = math::xml_parse_float(element->FirstChildElement("shininess"), shininess_);

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

	p->get_uniform(glutpp::uniform_name::e::FRONT_AMBIENT)->load_4fv(raw_.ambient_);
	p->get_uniform(glutpp::uniform_name::e::FRONT_DIFFUSE)->load_4fv(raw_.diffuse_);
	p->get_uniform(glutpp::uniform_name::e::FRONT_SPECULAR)->load_4fv(raw_.specular_);
	p->get_uniform(glutpp::uniform_name::e::FRONT_EMISSION)->load_4fv(raw_.emission_);
	p->get_uniform(glutpp::uniform_name::e::FRONT_SHININESS)->load(raw_.shininess_);
}
void glutpp::material::material::step(double time) {
		
	raw_.diffuse_.step(time);
}


