#include <neb/gfx/Context/Util/Cast.hh>
#include <neb/gfx/Context/Base.hh>
#include <neb/gfx/Context/Window.hpp>
#include <neb/gfx/Context/fbo.hpp>

std::shared_ptr<neb::gfx::context::base>		neb::gfx::context::util::cast::isContextBase() {
	return std::dynamic_pointer_cast<neb::gfx::context::base>(shared_from_this());
}
std::shared_ptr<neb::gfx::context::window>		neb::gfx::context::util::cast::isContextWindow() {
	return std::dynamic_pointer_cast<neb::gfx::context::window>(shared_from_this());
}
std::shared_ptr<neb::gfx::context::fbo>			neb::gfx::context::util::cast::isContextFBO() {
	return std::dynamic_pointer_cast<neb::gfx::context::fbo>(shared_from_this());
}

