#include <math/free.h>


#include <glutpp/config.h>

#include <glutpp/shape/desc.h>
#include <glutpp/shape/shape.h>
#include <glutpp/light/desc.h>
#include <glutpp/light/light.h>


glutpp::shape::desc::desc() {
	GLUTPP_DEBUG_0_FUNCTION;
}
void	glutpp::shape::desc::load(tinyxml2::XMLElement* element) {

	GLUTPP_DEBUG_0_FUNCTION;

	get_raw()->load(element);
	
	// lights
	tinyxml2::XMLElement* element_light = element->FirstChildElement("light");
	light::desc_s ld;
	
	while(element_light)
	{
		ld.reset(new glutpp::light::desc);
		
		ld->raw_.load(element_light);
		
		get_lights()->vec_.push_back(std::make_tuple(ld));

		element_light = element_light->NextSiblingElement("light");
	}
}
void glutpp::shape::desc::load(glutpp::shape::shape_s shape) {

	get_id()->i_ = shape->i();
	*get_raw() = shape->raw_;
	
	// shape
	glutpp::shape::desc_s sd;
	for(auto it = shape->shapes_.begin(); it != shape->shapes_.end(); ++it)
	{
		auto shape = it->second;
		
		sd.reset(new glutpp::shape::desc);
		
		sd->load(shape);
		
		get_shapes()->vec_.push_back(std::make_tuple(sd));
	}


	// light
	glutpp::light::desc_s ld;
	for(auto it = shape->lights_.begin(); it != shape->lights_.end(); ++it)
	{
		auto light = it->second;

		ld.reset(new glutpp::light::desc);

		ld->load(light);
		
		get_lights()->vec_.push_back(std::make_tuple(ld));
	}
}
glutpp::shape::id_s glutpp::shape::desc::get_id() {
	auto p = std::get<3>(tup_);
	assert(p);
	return p;
}
glutpp::shape::raw_s glutpp::shape::desc::get_raw() {
	auto p = std::get<2>(tup_);
	assert(p);
	return p;
}
glutpp::shape::vec_shape_desc_s glutpp::shape::desc::get_shapes() {
	auto p = std::get<1>(tup_);
	assert(p);
	return p;
}
glutpp::shape::vec_light_desc_s glutpp::shape::desc::get_lights() {
	auto p = std::get<0>(tup_);
	assert(p);
	return p;
}









