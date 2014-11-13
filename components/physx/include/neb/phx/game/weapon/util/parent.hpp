#ifndef PHYSX_GAME_WEAPON_UTIL_PARENT_HPP
#define PHYSX_GAME_WEAPON_UTIL_PARENT_HPP


#include <neb/core/util/parent.hpp>

#include <neb/phx/game/weapon/base.hpp>

namespace neb { namespace phx { namespace game { namespace weapon { namespace util {


	/** @brief @Parent
	 * abstract class for parent of a shape
	 */
	class parent:
		virtual public neb::util::parent<neb::phx::game::weapon::base>
	{
		public:
			virtual ~parent() {}
	};



}}}}}

#endif





