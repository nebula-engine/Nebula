//#include <math/free.hpp>

#include <Nebula/Graphics/light/desc.hpp>
#include <Nebula/Graphics/light/light.hpp>

/*
void Neb::light::raw::load(Neb::light::light_s light) {
	operator=(light->raw_);
}
void Neb::light::id::load(Neb::light::light_s light) {
	i_ = light->i_;
}
*/



Neb::light::desc::desc() {
}
void		Neb::light::desc::load(Neb::light::light_w light) {
	auto s_light = light.lock();
	assert(s_light);

	i_ = s_light->i_;

	raw_.load(light);
	
	raw_.print();
}






