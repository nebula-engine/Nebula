#ifndef NEBULA_GRAPHICS_CONTEXT_UTIL_CAST_HH
#define NEBULA_GRAPHICS_CONTEXT_UTIL_CAST_HH

#include <neb/core/itf/shared.hpp>

#include <neb/gfx/util/decl.hpp>

namespace neb {
	namespace gfx {
		namespace context {
			namespace util {
				/** @brief %Cast
				*/
				class cast:
					virtual public neb::itf::shared
				{
					public:
						std::shared_ptr<neb::gfx::context::base>			isContextBase();
						std::shared_ptr<neb::gfx::context::window>			isContextWindow();
						std::shared_ptr<neb::gfx::context::fbo>				isContextFBO();
				};
			}
		}
	}
}


#endif





