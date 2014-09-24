#ifndef NEB_FIN_GFX_PHX_CORE_SCENE_UTIL_PARENT_HPP
#define NEB_FIN_GFX_PHX_CORE_SCENE_UTIL_PARENT_HPP

#include <neb/gfx/core/scene/util/parent.hpp>

#include <neb/phx/core/scene/util/parent.hpp>

namespace neb {
	namespace fin {
		namespace gfx_phx {
			namespace core {
				namespace scene {
					namespace util {
						class parent:
							virtual public neb::gfx::core::scene::util::parent,
							virtual public neb::phx::core::scene::util::parent
						{
						};
					}
				}
			}
		}
	}
}

#endif
