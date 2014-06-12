#include <Nebula/Graphics/Window/Util/Cast.hh>
#include <Nebula/Graphics/Window/Base.hh>

sp::shared_ptr<neb::gfx::Window::Base>	neb::gfx::Window::Util::Cast::isWindowBase() {
	return sp::dynamic_pointer_cast<neb::gfx::Window::Base>(shared_from_this());
}

