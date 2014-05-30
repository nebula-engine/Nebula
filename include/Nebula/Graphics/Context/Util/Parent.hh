#ifndef NEBULA_GRAPHICS_CONTEXT_UTIL_PARENT_HH
#define NEBULA_GRAPHICS_CONTEXT_UTIL_PARENT_HH

#include <Nebula/Graphics/Window/Util/Cast.hh>
#include <Nebula/Graphics/Context/Base.hh>

namespace Neb {
	namespace Graphics {
		namespace Context {
			namespace Util {
				class Parent:
					virtual public Neb::Util::Parent<Neb::Graphics::Context::Base>,
					virtual public Neb::Graphics::Window::Util::Cast
				{
					public:
				};
			}
		}
	}
}

#endif





