#ifndef NEBULA_GRAPHICS_CONTEXT_UTIL_CAST_HH
#define NEBULA_GRAPHICS_CONTEXT_UTIL_CAST_HH

#include <Nebula/util/shared.hpp>
#include <Nebula/gfx/util/decl.hpp>

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





