#include <Nebula/Graphics/Context/Window.hpp>

Neb::Graphics::Context::Window::Window(sp::shared_ptr<Neb::Graphics::Window::Base> window):
	Neb::Graphics::Context::Base(window),
	window_(window)
{
}
void		Neb::Graphics::Context::Window::init() {
	Neb::Graphics::Context::Base::init();
	
	assert(window_);

	resize(window_->w_, window_->h_);
}


