#include <Nebula/Graphics/Context/Util/Cast.hh>
#include <Nebula/Graphics/Context/Base.hh>

sp::shared_ptr<neb::gfx::Context::Base>		neb::gfx::Context::Util::Cast::isContextBase() {
	return sp::dynamic_pointer_cast<neb::gfx::Context::Base>(shared_from_this());
}

