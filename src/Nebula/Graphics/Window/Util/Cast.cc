#include <Nebula/Graphics/Window/Util/Cast.hh>
#include <Nebula/Graphics/Window/Base.hh>

Neb::Graphics::Window::Base_s	Neb::Graphics::Window::Util::Cast::isWindowBase() {
	return std::dynamic_pointer_cast<Neb::Graphics::Window::Base>(shared_from_this());
}

