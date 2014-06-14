#ifndef NEBULA_GRAPHICS_WINDOW_UTIL_CAST_HH
#define NEBULA_GRAPHICS_WINDOW_UTIL_CAST_HH

#include <Nebula/Util/shared.hpp>
#include <Nebula/Graphics/Types.hh>

namespace neb {
	namespace gfx {
		namespace window {
			namespace util {
				class Cast:
					virtual public neb::std::shared
				{
					public:
						sp::shared_ptr<neb::gfx::window::base>		isWindowBase();
				};
			}
		}
	}
}

#endif



