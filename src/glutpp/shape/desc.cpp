#include <math/free.h>


#include <glutpp/config.h>
#include <glutpp/shape/desc.h>
#include <glutpp/light/desc.h>

void	glutpp::shape::raw::reset() {
	
	pose_.from_math(math::transform());
}
void	glutpp::shape::raw::load(tinyxml2::XMLElement* element)
{
	parse_type(element->Attribute("type"));

	switch(type_)
	{
		case glutpp::shape::type::BOX:
			box(element);
			break;
		case glutpp::shape::type::SPHERE:
			sphere(element);
			break;
		default:
			break;
	}

	front_.load(element->FirstChildElement("front"));
}
void	glutpp::shape::raw::parse_type(char const * str)
{
	assert(str);
	if(strcmp(str,"box") == 0)
	{
		type_ = glutpp::shape::type::BOX;
	}
	else if(strcmp(str,"sphere") == 0)
	{
		type_ = glutpp::shape::type::SPHERE;
	}
	else if(strcmp(str,"empty") == 0)
	{
		type_ = glutpp::shape::type::EMPTY;
	}
	else
	{
		printf("invalid shape type\n");
		abort();
	}
}


void	glutpp::shape::desc::reset() {

	raw_.reset();
}
void	glutpp::shape::desc::load(tinyxml2::XMLElement* element)
{
	raw_.load(element);
	
	// lights
	tinyxml2::XMLElement* element_light = element->FirstChildElement("light");
	light::desc* ld = NULL;
	
	while(element_light)
	{
		ld = new glutpp::light::desc;
		
		ld->raw_.load(element_light);
		
		lights_.push_back(ld);

		element_light = element_light->NextSiblingElement("light");
	}

}
void glutpp::shape::raw::box(math::vec3 ns)
{
	type_ = glutpp::shape::type::BOX;

	s_.from_math(ns);
}
void glutpp::shape::raw::box(tinyxml2::XMLElement* element)
{
	type_ = glutpp::shape::type::BOX;

	s_.from_math(math::xml_parse_vec3(element->FirstChildElement("s"), math::vec3(1,1,1)));
}
void glutpp::shape::raw::sphere(float r)
{
	type_ = glutpp::shape::type::SPHERE;

	s_.from_math(math::vec3(r, r, r));
}
void glutpp::shape::raw::sphere(tinyxml2::XMLElement* element)
{
	type_ = glutpp::shape::type::SPHERE;

	float r = math::xml_parse_float(element->FirstChildElement("s"));
	s_.from_math(math::vec3(r, r, r));
}







