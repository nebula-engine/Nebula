#include <stdio.h>

#include <math/free.h>

#include <glutpp/window.h>
#include <glutpp/scene.h>
#include <glutpp/material.h>





void	glutpp::material_desc::load(tinyxml2::XMLElement* element) {
	
	if(element == NULL)
	{
		printf("no element\n");
		return;
	}
	
	ambient_.from_math(math::xml_parse_color(element->FirstChildElement("ambient"), ambient_.to_math()));
	diffuse_.from_math(math::xml_parse_color(element->FirstChildElement("diffuse"), diffuse_.to_math()));
	specular_.from_math(math::xml_parse_color(element->FirstChildElement("specular"), specular_.to_math()));
	emission_.from_math(math::xml_parse_color(element->FirstChildElement("emission"), emission_.to_math()));
}




glutpp::material::material():
	ambient_(0.1,0.1,0.1,1.0),
	diffuse_(math::cyan),
	specular_(math::white),
	emission_(math::black),
	shininess_(500)
{}
void	glutpp::material::load(glutpp::material_desc desc) {
	
	ambient_ = desc.ambient_.to_math();
	diffuse_ = desc.diffuse_.to_math();
	specular_ = desc.specular_.to_math();
	emission_ = desc.emission_.to_math();
	
}
void	glutpp::material::init()
{
	printf("%s\n",__PRETTY_FUNCTION__);
}

void	glutpp::material::load()
{
	auto p = glutpp::__master.current_program();

	p->get_uniform(glutpp::uniform_name::e::FRONT_AMBIENT)->load_4fv(ambient_);
	p->get_uniform(glutpp::uniform_name::e::FRONT_DIFFUSE)->load_4fv(diffuse_);
	p->get_uniform(glutpp::uniform_name::e::FRONT_SPECULAR)->load_4fv(specular_);
	p->get_uniform(glutpp::uniform_name::e::FRONT_EMISSION)->load_4fv(emission_);
	p->get_uniform(glutpp::uniform_name::e::FRONT_SHININESS)->load(shininess_);
}



