#ifndef NEBULA_GRAPHICS_CONTEXT_UTIL_PARENT_HH
#define NEBULA_GRAPHICS_CONTEXT_UTIL_PARENT_HH

#include <Nebula/Util/parent.hpp>
#include <Nebula/Graphics/Window/Util/Cast.hh>
#include <Nebula/Graphics/Context/Base.hh>

namespace neb {
	namespace gfx {
		namespace Context {
			namespace Util {
				class Parent:
					virtual public neb::Util::parent< neb::gfx::Context::Base >,
					virtual public neb::gfx::Window::Util::Cast
				{
					public:
						virtual void			init() {}
						virtual void			step(neb::core::TimeStep const & ts) { neb::Util::parent< neb::gfx::Context::Base >::step(ts); }

				};
			}
		}
	}
}

#endif





