#include <math/free.h>


#include <glutpp/config.h>

#include <glutpp/shape/desc.h>
#include <glutpp/light/desc.h>

glutpp::shape::desc::desc() {
	
	GLUTPP_DEBUG_0_FUNCTION;
	
	reset();
}
void	glutpp::shape::raw::reset() {

	GLUTPP_DEBUG_0_FUNCTION;

	pose_.from_math(math::transform());
	
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
	program_ = glutpp::program_name::LIGHT;

	// material
	front_.load(element->FirstChildElement("front"));	
	
	// image
	tinyxml2::XMLElement* element_image = element->FirstChildElement("image");
	
	if(element_image != NULL)
	{
		char const * text = element_image->GetText();
		
		if(text != NULL)
		{
			size_t len = std::max(strlen(text), (size_t)max_filename_length);
			
			memcpy(image_, text, len);
			
			program_ = glutpp::program_name::IMAGE;
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





void	glutpp::shape::desc::reset() {

	raw_.reset();
}
void	glutpp::shape::desc::load(tinyxml2::XMLElement* element) {

	GLUTPP_DEBUG_0_FUNCTION;

	raw_.load(element);
	
	// lights
	tinyxml2::XMLElement* element_light = element->FirstChildElement("light");
	light::desc_shared ld;
	
	while(element_light)
	{
		ld.reset(new glutpp::light::desc);
		
		ld->raw_.load(element_light);
		
		lights_.push_back(ld);

		element_light = element_light->NextSiblingElement("light");
	}
}
size_t glutpp::shape::desc::size() {

	GLUTPP_DEBUG_0_FUNCTION;

	size_t s = sizeof(glutpp::shape::raw);

	for(auto it = shapes_.begin(); it != shapes_.end(); ++it)
	{
		auto shape = *it;

		assert(shape);

		s += shape->size();
	}
	
	for(auto it = lights_.begin(); it != lights_.end(); ++it)
	{
		auto light = *it;

		assert(light);

		s += light->size();
	}
	
	
	return s;
}
void glutpp::shape::desc::write(char*& head) {
	
	GLUTPP_DEBUG_0_FUNCTION;

	size_t len = sizeof(glutpp::shape::raw);

	raw_.shape_size_ = shapes_.size();
	raw_.light_size_ = lights_.size();
	
	printf("shape_size_ = %i\n", (int)raw_.shape_size_);
	printf("light_size_ = %i\n", (int)raw_.light_size_);

	memcpy(head, &raw_, len);
	head += len;
	
	for(auto it = shapes_.begin(); it != shapes_.end(); ++it)
	{
		auto shape = *it;
		assert(shape);
		
		shape->write(head);
	}

 	for(auto it = lights_.begin(); it != lights_.end(); ++it)
	{
		auto light = *it;
		assert(light);

		light->write(head);
	}
}
void glutpp::shape::desc::read(char*& head) {

	GLUTPP_DEBUG_0_FUNCTION;

	memcpy(&raw_, head, sizeof(glutpp::shape::raw));
	head += sizeof(glutpp::shape::raw);

	printf("shape_size_ = %i\n", (int)raw_.shape_size_);
	printf("light_size_ = %i\n", (int)raw_.light_size_);

	// shapes
	for(int i = 0; i < raw_.shape_size_; ++i)
	{
		glutpp::shape::desc_shared sd(new glutpp::shape::desc);

		sd->read(head);
		
		shapes_.push_back(sd);
	}

	// lights
	for(int i = 0; i < raw_.light_size_; ++i)
	{
		glutpp::light::desc_shared ld(new glutpp::light::desc);

		ld->read(head);

		lights_.push_back(ld);
	}
}











