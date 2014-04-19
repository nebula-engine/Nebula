#include <math/free.hpp>

#include <gru/shape/raw.hpp>


glutpp::shape::raw_base::raw_base():
	flag_(0)
{
	GLUTPP_DEBUG_0_FUNCTION;
	
	memset(image_, '\0', max_filename_length);
}
void	glutpp::shape::raw_base::load(tinyxml2::XMLElement* element)
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
void	glutpp::shape::raw_base::parse_type(char const * str) {
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
void glutpp::shape::raw_base::box(math::vec3<double> ns) {
	type_ = glutpp::shape::type::BOX;
	
	s_ = ns;
}
void glutpp::shape::raw_base::box(tinyxml2::XMLElement* element) {
	type_ = glutpp::shape::type::BOX;
	
	s_ = math::xml_parse_vec3(element->FirstChildElement("s"), math::vec3<double>(1,1,1));
}
void glutpp::shape::raw_base::sphere(float r) {
	type_ = glutpp::shape::type::SPHERE;
	
	s_ = math::vec3<double>(r, r, r);
}
void glutpp::shape::raw_base::sphere(tinyxml2::XMLElement* element) {
	type_ = glutpp::shape::type::SPHERE;

	float r = math::xml_parse_float(element->FirstChildElement("s"));
	s_ = math::vec3<double>(r, r, r);
}



glutpp::shape::raw& glutpp::shape::raw::operator=(glutpp::shape::raw const & rhs) {
	
	*get_raw_base() = *rhs.get_raw_base();
	*get_vec_mat()  = *rhs.get_vec_mat();
	
}
glutpp::shape::raw_base_s glutpp::shape::raw::get_raw_base() const {
	auto p = std::get<0>(tup_);
	assert(p);
	return p;
}
glutpp::shape::vec_mat_s glutpp::shape::raw::get_vec_mat() const {
	auto p = std::get<1>(tup_);
	assert(p);
	return p;
}
void glutpp::shape::raw::load(tinyxml2::XMLElement* element) {
	GLUTPP_DEBUG_0_FUNCTION;
	printf("%s\n", element->Name());
	
	get_raw_base()->load(element);
	
	tinyxml2::XMLElement* e = element->FirstChildElement("front");
	
	while(e != NULL)
	{
		glutpp::material::raw m;
		m.load(e);
		
		get_vec_mat()->vec_.push_back(m);
		
		e = e->NextSiblingElement("front");	
	}
	
	//assert(get_vec_mat()->vec_.size() > 0);
}









