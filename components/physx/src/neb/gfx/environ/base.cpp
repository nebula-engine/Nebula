#include <neb/gfx/environ/base.hpp>

void		neb::gfx::environ::base::init() {
}
void		neb::gfx::environ::base::step(gal::etc::timestep const & ts) {
}
void		neb::gfx::environ::base::resize(int w, int h) {
	viewport_.resize(w,h);
}
bool		neb::gfx::environ::base::shouldRender()
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	return true;
}


