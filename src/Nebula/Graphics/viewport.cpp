#include <Nebula/Graphics/Viewport.hpp>
#include <Nebula/Util/typedef.hpp>

void		Neb::gfx::Viewport::load() {
	glViewport(x_, y_, w_, h_);
}
void		Neb::gfx::Viewport::resize(int w, int h) {
	w_ = w;
	h_ = h;
	
	aspect_ = (real)w_ / (real)h_;
}

