#ifndef NEBULA_CORE_LIGHT_GFX_UTIL_PARENT_HH
#define NEBULA_CORE_LIGHT_GFX_UTIL_PARENT_HH

#include <neb/core/core/light/util/light_count.hpp>
#include <neb/core/core/light/util/parent.hpp>

namespace neb { namespace gfx { namespace core {
	namespace light {
		namespace util {
			class parent:
				virtual public neb::core::core::light::util::parent
			{
				public:
					virtual ~parent() {}
					void			setPose(
							neb::core::pose const & pose);
					void			load_lights(
							neb::core::core::light::util::count & light_count,
							neb::core::pose const & pose);
			};
		}
	}
}}}

#endif
