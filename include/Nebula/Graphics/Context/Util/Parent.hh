#ifndef NEBULA_GRAPHICS_CONTEXT_UTIL_PARENT_HH
#define NEBULA_GRAPHICS_CONTEXT_UTIL_PARENT_HH

#include <Nebula/Util/parent.hpp>
#include <Nebula/Graphics/Window/Util/Cast.hh>
#include <Nebula/Graphics/Context/Base.hh>

namespace neb {
	namespace gfx {
		namespace context {
			namespace util {
				class parent:
					virtual public neb::util::parent< neb::gfx::context::base >,
					virtual public neb::gfx::window::util::cast
				{
					public:
						virtual void			init() {}
						virtual void			step(neb::core::TimeStep const & ts) { neb::util::parent< neb::gfx::context::base >::step(ts); }

				};
			}
		}
	}
}

#endif





