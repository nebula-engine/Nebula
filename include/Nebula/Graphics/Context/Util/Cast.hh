#ifndef NEBULA_GRAPHICS_CONTEXT_UTIL_CAST_HH
#define NEBULA_GRAPHICS_CONTEXT_UTIL_CAST_HH

#include <Nebula/Util/shared.hpp>
#include <Nebula/Graphics/Types.hh>

namespace neb {
	namespace gfx {
		namespace context {
			namespace util {
				/** @brief %Cast
				*/
				class cast:
					virtual public neb::std::shared
				{
					public:
						sp::shared_ptr<neb::gfx::context::base>			isContextBase();
				};
			}
		}
	}
}


#endif





