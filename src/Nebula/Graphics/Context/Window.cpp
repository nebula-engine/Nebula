#include <Nebula/Graphics/Context/Window.hpp>

neb::gfx::Context::Window::Window(sp::shared_ptr<neb::gfx::Window::Base> window):
	neb::gfx::Context::Base(window),
	window_(window)
{
}
void		neb::gfx::Context::Window::init() {
	neb::gfx::Context::Base::init();
	
	assert(window_);

	resize(window_->w_, window_->h_);
}


