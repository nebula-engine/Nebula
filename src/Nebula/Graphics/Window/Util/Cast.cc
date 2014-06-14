#include <Nebula/Graphics/Window/Util/Cast.hh>
#include <Nebula/Graphics/Window/Base.hh>

sp::shared_ptr<neb::gfx::window::base>	neb::gfx::window::util::Cast::isWindowBase() {
	return sp::dynamic_pointer_cast<neb::gfx::window::base>(shared_from_this());
}

