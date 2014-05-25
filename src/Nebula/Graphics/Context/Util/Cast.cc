#include <Nebula/Graphics/Context/Util/Cast.hh>
#include <Nebula/Graphics/Context/Base.hh>

Neb::Graphics::Context::Base_s		Neb::Graphics::Context::Util::Cast::isContextBase() {
	return std::dynamic_pointer_cast<Neb::Graphics::Context::Base>(shared_from_this());
}

