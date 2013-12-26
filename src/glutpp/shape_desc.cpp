#include <math/free.h>


#include <glutpp/types.h>
#include <glutpp/shape_desc.h>

void	glutpp::shape_desc::reset() {
}
void	glutpp::shape_desc::parse_type(char const * str)
{
	assert(str);
	if(strcmp(str,"box") == 0)
	{
		type_ = glutpp::shape_type::BOX;
	}
	else if(strcmp(str,"sphere") == 0)
	{
		type_ = glutpp::shape_type::SPHERE;
	}
	else
	{
		printf("invalid shape type\n");
		exit(0);
	}
}
void	glutpp::shape_desc::parse_xml(tinyxml2::XMLElement* element)
{
	parse_type(element->Attribute("type"));

	switch(type_)
	{
		case glutpp::shape_type::BOX:
			box(element);
			break;
		case glutpp::shape_type::SPHERE:
			sphere(element);
			break;
		default:
			break;
	}
	
	front_.load(element->FirstChildElement("front"));
}
int                     glutpp::shape_desc::box(math::vec3 ns)
{
        type_ = glutpp::shape_type::BOX;

        s_.from_math(ns);

        return 0;
}
int                     glutpp::shape_desc::box(tinyxml2::XMLElement* element)
{
        type_ = glutpp::shape_type::BOX;

        s_.from_math(math::xml_parse_vec3(element->FirstChildElement("s")));

        return 0;
}
int                     glutpp::shape_desc::sphere(float r)
{
        type_ = glutpp::shape_type::SPHERE;

        s_.from_math(math::vec3(r, r, r));

        return 0;
}
int                     glutpp::shape_desc::sphere(tinyxml2::XMLElement* element)
{
        type_ = glutpp::shape_type::SPHERE;

        float r = math::xml_parse_float(element->FirstChildElement("s"));
        s_.from_math(math::vec3(r, r, r));

        return 0;
}







