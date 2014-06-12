#ifndef NEBULA_GRAPHICS_CONTEXT_UTIL_PARENT_HH
#define NEBULA_GRAPHICS_CONTEXT_UTIL_PARENT_HH

#include <Nebula/Graphics/Window/Util/Cast.hh>
#include <Nebula/Graphics/Context/Base.hh>

namespace neb {
	namespace gfx {
		namespace Context {
			namespace Util {
				class Parent:
					virtual public gal::std::parent< neb::gfx::Context::Base >,
					virtual public neb::gfx::Window::Util::Cast
				{
					public:
				};
			}
		}
	}
}

#endif





