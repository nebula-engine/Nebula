
#include <math/xml.hpp>

#include <gru/light/raw.hpp>

glutpp::light::raw::raw():
	pos_(math::vec4<double>(0.0, 0.0, 0.0, 1.0)),
	ambient_(math::Color::black),
	diffuse_(math::Color::white),
	specular_(math::Color::white),
	spot_direction_(math::vec3<double>(0.0, 0.0, -1.0)),
	spot_cutoff_(10.0),
	spot_exponent_(1.0),
	atten_const_(1.0),
	atten_linear_(0.0),
	atten_quad_(0.0)
{
	GLUTPP_DEBUG_0_FUNCTION;
}
void	glutpp::light::raw::load(tinyxml2::XMLElement* element) {
	GLUTPP_DEBUG_0_FUNCTION;

	pos_ = math::Xml::parse_vec4<double>(element->FirstChildElement("p"));
	
	ambient_ = math::Xml::parse_color<double>(
			element->FirstChildElement("ambient"),
			ambient_);
	
	diffuse_ = math::Xml::parse_color<double>(
			element->FirstChildElement("diffuse"),
			diffuse_);
	
	specular_ = math::Xml::parse_color<double>(
			element->FirstChildElement("specular"),
			specular_);
	
	
	
	spot_direction_ = math::Xml::parse_vec3<double>(
		element->FirstChildElement("spot_direction"),
		math::vec3<double>(0.0, 0.0, 0.0));
	
	spot_cutoff_           = math::Xml::parse_float<double>(element->FirstChildElement("spot_cutoff"), M_PI);
	spot_exponent_         = math::Xml::parse_float<double>(element->FirstChildElement("spot_exponent"), 0.0);
	spot_light_cos_cutoff_ = math::Xml::parse_float<double>(element->FirstChildElement("spot_cutoff"), M_PI);
	
	
	atten_const_  = math::Xml::parse_float<double>(element->FirstChildElement("atten_const"), 1.0);
	atten_linear_ = math::Xml::parse_float<double>(element->FirstChildElement("atten_linear"), 0.0);
	atten_quad_   = math::Xml::parse_float<double>(element->FirstChildElement("atten_quad"), 0.0);
	
	print();
}
void	glutpp::light::raw::print() {

	pos_.print();
	printf("pos_                   = % 2.1f % 2.1f % 2.1f % 2.1f\n",
			pos_.x(), pos_.y(), pos_.z(), pos_.w());
	printf("ambient_               = % 2.1f % 2.1f % 2.1f % 2.1f\n",
			ambient_.r, ambient_.g, ambient_.b, ambient_.a);
	printf("diffuse_               = % 2.1f % 2.1f % 2.1f % 2.1f\n",
			diffuse_.r, diffuse_.g, diffuse_.b, diffuse_.a);
	printf("specular_              = % 2.1f % 2.1f % 2.1f % 2.1f\n",
			specular_.r, specular_.g, specular_.b, specular_.a);
	spot_direction_.print();
	printf("spot_cutoff_           = % 2.1f\n", spot_cutoff_);
	printf("spot_exponent_         = % 2.1f\n", spot_exponent_);
	printf("spot_light_cos_cutoff_ = % 2.1f\n", spot_light_cos_cutoff_);
	printf("atten_const_           = % 2.1f\n", atten_const_);
	printf("atten_linear_          = % 2.1f\n", atten_linear_);
	printf("atten_quad_            = % 2.1f\n", atten_quad_);
}

