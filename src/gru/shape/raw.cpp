//#include <math/config.hpp>
//#include <math/free.hpp>

#include <gru/free.hpp>
#include <gru/Xml/Xml.hpp>
#include <gru/shape/raw.hpp>


glutpp::shape::Raw::Raw():
	flag_(0)
{
	GLUTPP_DEBUG_0_FUNCTION;
	
	memset(image_, '\0', max_filename_length);
	memset(normal_, '\0', max_filename_length);
}
/*
void	glutpp::shape::raw_base::load(tinyxml2::XMLElement* element) {
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
*/
/*
void	glutpp::shape::Raw::parse_type(char const * str) {
	assert(str);
	int type;
	if(strcmp(str,"box") == 0)
	{
		type = glutpp::shape::type::BOX;
	}
	else if(strcmp(str,"sphere") == 0)
	{
		type = glutpp::shape::type::SPHERE;
	}
	else if(strcmp(str,"empty") == 0)
	{
		type = glutpp::shape::type::EMPTY;
	}
	else
	{
		printf("invalid shape type\n");
		abort();
	}

}
*/

glutpp::shape::Raw& glutpp::shape::Raw::operator=(glutpp::shape::Raw const & rhs) {
	// copy raw_base_
	//raw_base_.reset(new_copy(rhs.raw_base_));
	


	// copy material
	material_ = rhs.material_;

	return *this;
}
/*
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
*/
/*
void glutpp::shape::raw::load(tinyxml2::XMLElement* element) {
	GLUTPP_DEBUG_0_FUNCTION;
	printf("%s\n", element->Name());

	XmlArchive ar(element);
	
	//raw_base_->load(element);
	raw_base_->serialize(ar);
	
	tinyxml2::XMLElement* e = element->FirstChildElement("front");
	
	while(e != NULL) {
		glutpp::material::raw_s m(new glutpp::material::raw(e));
		//m.load(e);
		
		materials_.push_back(m);
		
		e = e->NextSiblingElement("front");	
	}
	
	//assert(get_vec_mat()->vec_.size() > 0);
}
*/








