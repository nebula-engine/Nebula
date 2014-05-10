//#include <math/config.hpp>
//#include <math/free.hpp>

#include <Nebula/free.hpp>
#include <Nebula/Xml/Xml.hpp>
#include <Nebula/shape/raw.hpp>


Neb::Shape::Raw::Raw() {
	//GLUTPP_DEBUG_0_FUNCTION;
	
}
/*
void	Neb::Shape::raw_base::load(tinyxml2::XMLElement* element) {
	GLUTPP_DEBUG_0_FUNCTION;
	
	parse_type(element->Attribute("type"));

	switch(type_)
	{
		case Neb::Shape::type::BOX:
			box(element);
			break;
		case Neb::Shape::type::SPHERE:
			sphere(element);
			break;
		default:
			break;
	}
	
	// program
	//program_ = Neb::program_name::LIGHT;
	
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
			
			//program_ = Neb::program_name::IMAGE;
		}
	}
	
	printf("image = '%s'\n", image_);
}
*/
/*
void	Neb::Shape::Raw::parse_type(char const * str) {
	assert(str);
	int type;
	if(strcmp(str,"box") == 0)
	{
		type = Neb::Shape::type::BOX;
	}
	else if(strcmp(str,"sphere") == 0)
	{
		type = Neb::Shape::type::SPHERE;
	}
	else if(strcmp(str,"empty") == 0)
	{
		type = Neb::Shape::type::EMPTY;
	}
	else
	{
		printf("invalid shape type\n");
		abort();
	}

}
*/

Neb::Shape::Raw& Neb::Shape::Raw::operator=(Neb::Shape::Raw const & rhs) {
	// copy raw_base_
	//raw_base_.reset(new_copy(rhs.raw_base_));
	


	// copy material
	material_ = rhs.material_;

	return *this;
}
/*
Neb::Shape::raw_base_s Neb::Shape::raw::get_raw_base() const {
	auto p = std::get<0>(tup_);
	assert(p);
	return p;
}
Neb::Shape::vec_mat_s Neb::Shape::raw::get_vec_mat() const {
	auto p = std::get<1>(tup_);
	assert(p);
	return p;
}
*/
/*
void Neb::Shape::raw::load(tinyxml2::XMLElement* element) {
	GLUTPP_DEBUG_0_FUNCTION;
	printf("%s\n", element->Name());

	XmlArchive ar(element);
	
	//raw_base_->load(element);
	raw_base_->serialize(ar);
	
	tinyxml2::XMLElement* e = element->FirstChildElement("front");
	
	while(e != NULL) {
		Neb::material::raw_s m(new Neb::material::raw(e));
		//m.load(e);
		
		materials_.push_back(m);
		
		e = e->NextSiblingElement("front");	
	}
	
	//assert(get_vec_mat()->vec_.size() > 0);
}
*/








