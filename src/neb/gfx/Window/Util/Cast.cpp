#include <neb/gfx/window/util/Cast.hh>
#include <neb/gfx/window/Base.hh>

sp::shared_ptr<neb::gfx::window::base>	neb::gfx::window::util::cast::isWindowBase() {
	return sp::dynamic_pointer_cast<neb::gfx::window::base>(shared_from_this());
}

