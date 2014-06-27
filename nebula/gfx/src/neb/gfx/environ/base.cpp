#include <neb/gfx/environ/base.hpp>

void		neb::gfx::environ::base::init() {
}
void		neb::gfx::environ::base::step(gal::std::timestep const & ts) {
}
void		neb::gfx::environ::base::resize(int w, int h) {
	viewport_.resize(w,h);
}


