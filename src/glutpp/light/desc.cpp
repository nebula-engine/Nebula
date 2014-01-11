#include <math/free.h>

#include <glutpp/light/desc.h>
#include <glutpp/light/light.h>




glutpp::light::raw::raw() {

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
void	glutpp::light::raw::load(tinyxml2::XMLElement* element) {
	GLUTPP_DEBUG_0_FUNCTION;

	pos_.from_math(math::xml_parse_vec4(element->FirstChildElement("p")));
	
	ambient_.from_math(math::xml_parse_color(element->FirstChildElement("ambient")));
	diffuse_.from_math(math::xml_parse_color(element->FirstChildElement("diffuse")));
	specular_.from_math(math::xml_parse_color(element->FirstChildElement("specular")));

	atten_linear_ = math::xml_parse_float(element->FirstChildElement("atten_linear"));
	
	print();
}
void	glutpp::light::raw::print() {

	printf("pos_                   = % 2.1f % 2.1f % 2.1f % 2.1f\n",
			pos_.x, pos_.y, pos_.z, pos_.w);
	printf("ambient_               = % 2.1f % 2.1f % 2.1f % 2.1f\n",
			ambient_.r, ambient_.g, ambient_.b, ambient_.a);
	printf("diffuse_               = % 2.1f % 2.1f % 2.1f % 2.1f\n",
			diffuse_.r, diffuse_.g, diffuse_.b, diffuse_.a);
	printf("specular_              = % 2.1f % 2.1f % 2.1f % 2.1f\n",
			specular_.r, specular_.g, specular_.b, specular_.a);
	printf("spot_direction_        = % 2.1f % 2.1f % 2.1f\n",
			spot_direction_.x, spot_direction_.y, spot_direction_.z);
	printf("spot_cutoff_           = % 2.1f\n", spot_cutoff_);
	printf("spot_exponent_         = % 2.1f\n", spot_exponent_);
	printf("spot_light_cos_cutoff_ = % 2.1f\n", spot_light_cos_cutoff_);
	printf("atten_const_           = % 2.1f\n", atten_const_);
	printf("atten_linear_          = % 2.1f\n", atten_linear_);
	printf("atten_quad_            = % 2.1f\n", atten_quad_);
}




glutpp::light::desc::desc() {
}
void glutpp::light::desc::load(glutpp::light::light_shared light) {
	i_ = light->i_;
	raw_ = light->raw_;
	
	raw_.print();
}
void glutpp::light::desc::write(gal::network::message_shared msg) {
	printf("%s\n",__PRETTY_FUNCTION__);
	
	msg->write(&raw_, sizeof(glutpp::light::raw));
	
	raw_.print();
}
void glutpp::light::desc::read(gal::network::message_shared msg) {
	printf("%s\n",__PRETTY_FUNCTION__);

	msg->read(&raw_, sizeof(glutpp::light::raw));

	raw_.print();
}
size_t glutpp::light::desc::size() {

	printf("%s\n",__PRETTY_FUNCTION__);
	
	return sizeof(glutpp::light::raw);
}





