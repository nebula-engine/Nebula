#ifndef NEBULA_GRAPHICS_CONTEXT_UTIL_CAST_HH
#define NEBULA_GRAPHICS_CONTEXT_UTIL_CAST_HH

#include <Nebula/Util/shared.hpp>
#include <Nebula/Graphics/Types.hh>

namespace neb {
	namespace gfx {
		namespace Context {
			namespace Util {
				/** @brief %Cast
				*/
				class Cast:
					virtual public neb::std::shared
				{
					public:
						sp::shared_ptr<neb::gfx::Context::Base>			isContextBase();
				};
			}
		}
	}
}


#endif





