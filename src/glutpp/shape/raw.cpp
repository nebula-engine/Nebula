#include <math/free.h>

#include <glutpp/shape/raw.h>


glutpp::shape::raw::raw():
	flag_(0)
{
	GLUTPP_DEBUG_0_FUNCTION;
	
	memset(image_, '\0', max_filename_length);
}
void	glutpp::shape::raw::load(tinyxml2::XMLElement* element)
{
	GLUTPP_DEBUG_0_FUNCTION;
	
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
	
	// program
	//program_ = glutpp::program_name::LIGHT;

	// material
	front_.raw_.load(element->FirstChildElement("front"));	
	
	// image
	tinyxml2::XMLElement* element_image = element->FirstChildElement("image");
	
	if(element_image != NULL)
	{
		char const * text = element_image->GetText();
		
		if(text != NULL)
		{
			size_t len = std::max(strlen(text), (size_t)max_filename_length);
			
			memcpy(image_, text, len);
			
			//program_ = glutpp::program_name::IMAGE;
		}
	}
	
	printf("image = '%s'\n", image_);
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
void glutpp::shape::raw::box(math::vec3 ns)
{
	type_ = glutpp::shape::type::BOX;
	
	s_ = ns;
}
void glutpp::shape::raw::box(tinyxml2::XMLElement* element)
{
	type_ = glutpp::shape::type::BOX;
	
	s_ = math::xml_parse_vec3(element->FirstChildElement("s"), math::vec3(1,1,1));
}
void glutpp::shape::raw::sphere(float r)
{
	type_ = glutpp::shape::type::SPHERE;
	
	s_ = math::vec3(r, r, r);
}
void glutpp::shape::raw::sphere(tinyxml2::XMLElement* element)
{
	type_ = glutpp::shape::type::SPHERE;

	float r = math::xml_parse_float(element->FirstChildElement("s"));
	s_ = math::vec3(r, r, r);
}






