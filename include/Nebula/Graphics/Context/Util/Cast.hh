#ifndef NEBULA_GRAPHICS_CONTEXT_UTIL_CAST_HH
#define NEBULA_GRAPHICS_CONTEXT_UTIL_CAST_HH

#include <Galaxy-Standard/shared.hpp>

#include <Nebula/Graphics/Types.hh>

namespace neb {
	namespace gfx {
		namespace Context {
			namespace Util {
				/** @brief %Cast
				*/
				class Cast:
					virtual public gal::std::shared
				{
					public:
						neb::gfx::Context::Base_s			isContextBase();
				};
			}
		}
	}
}


#endif





