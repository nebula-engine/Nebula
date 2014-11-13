#ifndef PHYSX_GAME_GAME_UTIL_PARENT_HPP
#define PHYSX_GAME_GAME_UTIL_PARENT_HPP


#include <neb/core/game/game/util/parent.hpp>

#include <neb/phx/game/game/base.hpp>

namespace neb {
	namespace phx {
		namespace game {
			namespace game {
				namespace util {
					/** @brief @Parent
					 * abstract class for parent of a shape
					 */
					class parent:
						virtual public neb::game::game::util::parent
					{
						public:
							virtual ~parent() {}
					};
				}
			}
		}
	}
}

#endif

