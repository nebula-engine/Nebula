#include <Nebula/Graphics/Context/Util/Cast.hh>
#include <Nebula/Graphics/Context/Base.hh>

sp::shared_ptr<neb::gfx::context::base>		neb::gfx::context::util::Cast::isContextBase() {
	return sp::dynamic_pointer_cast<neb::gfx::context::base>(shared_from_this());
}

