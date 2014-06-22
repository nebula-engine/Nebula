#include <Nebula/gfx/environ/two.hpp>
#include <Nebula/gfx/environ/three.hpp>
#include <Nebula/gfx/environ/util/cast.hpp>

sp::shared_ptr<neb::gfx::environ::two>		neb::gfx::environ::util::cast::isEnvironTwo() {
	return sp::dynamic_pointer_cast<neb::gfx::environ::two>(shared_from_this());
}
sp::shared_ptr<neb::gfx::environ::three>	neb::gfx::environ::util::cast::isEnvironThree() {
	return sp::dynamic_pointer_cast<neb::gfx::environ::three>(shared_from_this());
}

