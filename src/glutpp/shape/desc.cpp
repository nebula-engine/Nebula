#include <math/free.h>


#include <glutpp/config.h>

#include <glutpp/shape/desc.h>
#include <glutpp/shape/shape.h>
#include <glutpp/light/desc.h>
#include <glutpp/light/light.h>


glutpp::shape::desc::desc() {
	GLUTPP_DEBUG_0_FUNCTION;
	
	reset();
}
glutpp::shape::raw::raw() {

	GLUTPP_DEBUG_0_FUNCTION;

	pose_.from_math(math::transform());
	
	flag_ = 0;
	
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
		
		lights_.vec_.push_back(std::make_tuple(ld));

		element_light = element_light->NextSiblingElement("light");
	}
}
void glutpp::shape::desc::load(glutpp::shape::shape_shared shape) {

	i_ = shape->i();
	raw_ = shape->raw_;
	
	// shape
	glutpp::shape::desc_shared sd;
	for(auto it = shape->shapes_.begin(); it != shape->shapes_.end(); ++it)
	{
		auto shape = it->second;
		
		sd.reset(new glutpp::shape::desc);
		
		sd->load(shape);
		
		shapes_.vec_.push_back(std::make_tuple(sd));
	}


	// light
	glutpp::light::desc_shared ld;
	for(auto it = shape->lights_.begin(); it != shape->lights_.end(); ++it)
	{
		auto light = it->second;

		ld.reset(new glutpp::light::desc);

		ld->load(light);
		
		lights_.vec_.push_back(std::make_tuple(ld));
	}
}
size_t glutpp::shape::desc::size() {

	GLUTPP_DEBUG_0_FUNCTION;
	
	size_t s = 0;
	
	s += sizeof(int);
	s += sizeof(glutpp::shape::raw);
	s += shapes_.size();
	s += lights_.size();
	
	return s;
}
void glutpp::shape::desc::write(gal::network::message_shared msg) {
	GLUTPP_DEBUG_0_FUNCTION;
	
	msg->write(&i_, sizeof(int));
	msg->write(&raw_, sizeof(glutpp::shape::raw));
	
	shapes_.write(msg);
	lights_.write(msg);
}
void glutpp::shape::desc::read(gal::network::message_shared msg) {

	GLUTPP_DEBUG_0_FUNCTION;

	msg->read(&i_, sizeof(int));
	msg->read(&raw_, sizeof(glutpp::shape::raw));
	
	shapes_.read(msg);
	lights_.read(msg);

	
}











