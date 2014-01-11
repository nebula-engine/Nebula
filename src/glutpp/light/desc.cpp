#include <math/free.h>

#include <glutpp/light/desc.h>
#include <glutpp/light/light.h>








glutpp::light::desc::desc() {
}
void glutpp::light::desc::load(glutpp::light::light_s light) {
	i_ = light->i_;
	raw_ = light->raw_;
	
	raw_.print();
}






