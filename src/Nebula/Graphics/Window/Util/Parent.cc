#include <Nebula/Graphics/Window/Util/Parent.hh>

Neb::Graphics::Window::Util::Parent::Parent();
void		Neb::Graphics::Window::Util::Parent::insertWindow(Neb::Graphics::Window::Base_s window) {
	
	
	window_.push_back(window);
}

