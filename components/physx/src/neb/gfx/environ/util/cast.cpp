#include <neb/gfx/environ/two.hpp>
#include <neb/gfx/environ/three.hpp>
#include <neb/gfx/environ/util/cast.hpp>

std::shared_ptr<neb::gfx::environ::two>		neb::gfx::environ::util::cast::isEnvironTwo() {
	return std::dynamic_pointer_cast<neb::gfx::environ::two>(shared_from_this());
}
std::shared_ptr<neb::gfx::environ::three>	neb::gfx::environ::util::cast::isEnvironThree() {
	return std::dynamic_pointer_cast<neb::gfx::environ::three>(shared_from_this());
}

