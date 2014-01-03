#include <math/free.h>

#include <glutpp/light/desc.h>




void	glutpp::light::raw::reset() {

	pos_.from_math(math::vec4(0.0, 0.0, 0.0, 1.0));
	ambient_.from_math(math::white * 0.2f);
	diffuse_.from_math(math::white);
	specular_.from_math(math::white);
	spot_direction_.from_math(math::vec3(0.0, 0.0, -1.0));

	spot_cutoff_ 	= 10.0;
	spot_exponent_ 	= 1.0;
	atten_const_ 	= 1.0;
	atten_linear_ 	= 0.0;
	atten_quad_ 	= 0.0;

}
void	glutpp::light::raw::load(tinyxml2::XMLElement* element)
{
	pos_.from_math(math::xml_parse_vec4(element->FirstChildElement("p")));
	
	ambient_.from_math(math::xml_parse_color(element->FirstChildElement("ambient")));
	diffuse_.from_math(math::xml_parse_color(element->FirstChildElement("diffuse")));
	specular_.from_math(math::xml_parse_color(element->FirstChildElement("specular")));
	
	atten_linear_ = math::xml_parse_float(element->FirstChildElement("atten_linear"));
}







glutpp::light::desc::desc()
{
	raw_.reset();
}






