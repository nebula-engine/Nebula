#include <neb/gfx/window/util/Cast.hh>
#include <neb/gfx/window/Base.hh>

std::shared_ptr<neb::gfx::window::base>	neb::gfx::window::util::cast::isWindowBase() {
	return std::dynamic_pointer_cast<neb::gfx::window::base>(shared_from_this());
}

