#include <Nebula/gfx/Context/Util/Cast.hh>
#include <Nebula/gfx/Context/Base.hh>

sp::shared_ptr<neb::gfx::context::base>		neb::gfx::context::util::cast::isContextBase() {
	return sp::dynamic_pointer_cast<neb::gfx::context::base>(shared_from_this());
}

