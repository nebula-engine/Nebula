#include <Nebula/Graphics/Context/Window.hpp>

neb::gfx::context::window::window(sp::shared_ptr<neb::gfx::window::base> window):
	neb::gfx::context::base(window),
	window_(window)
{
}
void		neb::gfx::context::window::init() {
	neb::gfx::context::base::init();
	
	assert(window_);

	resize(window_->w_, window_->h_);
}


