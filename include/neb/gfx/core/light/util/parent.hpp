#ifndef NEBULA_CORE_LIGHT_GFX_UTIL_PARENT_HH
#define NEBULA_CORE_LIGHT_GFX_UTIL_PARENT_HH

#include <neb/core/shape/Util/Parent.hh>

namespace neb { namespace gfx { namespace core {
	namespace light {
		namespace util {
			class parent:
				virtual public neb::core::light::util::parent
			{
				public:
					virtual ~parent() {}
					
					
					void		load_lights(neb::core::light::util::count & light_count, neb::core::pose const & pose);

					
			};
		}
	}
}}}

#endif
