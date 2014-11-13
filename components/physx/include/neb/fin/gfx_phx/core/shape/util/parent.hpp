#ifndef NEB_FIN_GFX_PHX_CORE_SHAPE_UTIL_PARENT_HPP
#define NEB_FIN_GFX_PHX_CORE_SHAPE_UTIL_PARENT_HPP

#include <neb/gfx/core/shape/util/parent.hpp>
#include <neb/phx/core/shape/util/parent.hpp>

namespace neb {
	namespace fin {
		namespace gfx_phx {
			namespace core {
				namespace shape {
					namespace util {
						/** @brief %parent
						*/
						class parent:
							virtual public neb::gfx::core::shape::util::parent,
							virtual public neb::phx::core::shape::util::parent
						{
							public:

						};
					}
				}
			}
		}
	}
}

#endif


