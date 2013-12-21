#include <math/free.h>

#include <glutpp/desc_light.h>

glutpp::desc_light::desc_light():
	pos_(0.0, 0.0, 0.0, 1.0),
	ambient_(math::white * 0.2f),
	diffuse_(math::white),
	specular_(math::white),
	spot_direction_(0.0, 0.0, -1.0),
	spot_cutoff_(10.0),
	spot_exponent_(1.0),
	atten_const_(1.0),
	atten_linear_(0.0),
	atten_quad_(0.0)
{
}
void	glutpp::desc_light::load(tinyxml2::XMLElement* element)
{
	pos_ = math::xml_parse_vec4(element->FirstChildElement("p"));
	
	ambient_ = math::xml_parse_color(element->FirstChildElement("ambient"));
	diffuse_ = math::xml_parse_color(element->FirstChildElement("diffuse"));
	specular_ = math::xml_parse_color(element->FirstChildElement("specular"));
	
	atten_linear_ = math::xml_parse_float(element->FirstChildElement("atten_linear"));
}



