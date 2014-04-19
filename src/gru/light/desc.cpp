#include <math/free.hpp>

#include <gru/light/desc.hpp>
#include <gru/light/light.hpp>


void glutpp::light::raw::load(glutpp::light::light_s light) {
	operator=(light->raw_);
}


void glutpp::light::id::load(glutpp::light::light_s light) {
	i_ = light->i_;
}




glutpp::light::desc::desc() {
}
void glutpp::light::desc::load(glutpp::light::light_s light) {
	get_id()->load(light);
	get_raw()->load(light);
	
	get_raw()->print();
}






