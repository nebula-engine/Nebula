#ifndef NEBULA_GRAPHICS_CONTEXT_UTIL_CAST_HH
#define NEBULA_GRAPHICS_CONTEXT_UTIL_CAST_HH

#include <Nebula/Graphics/Types.hh>
#include <Nebula/Util/Shared.hh>

namespace Neb {
	namespace Graphics {
		namespace Context {
			namespace Util {
				/** @brief %Cast
				*/
				class Cast:
					virtual public Neb::Util::Shared
				{
					public:
						Neb::Graphics::Context::Base_s			isContextBase();
				};
			}
		}
	}
}


#endif





