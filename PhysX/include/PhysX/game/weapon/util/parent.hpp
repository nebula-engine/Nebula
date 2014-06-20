#ifndef PHYSX_GAME_WEAPON_UTIL_PARENT_HPP
#define PHYSX_GAME_WEAPON_UTIL_PARENT_HPP


#include <Nebula/util/parent.hpp>

#include <PhysX/game/weapon/base.hpp>

namespace phx { namespace game { namespace weapon { namespace util {



			/** @brief @Parent
			 * abstract class for parent of a shape
			 */
			class parent:
				virtual public neb::util::parent<phx::game::weapon::base>
			{
				public:
					virtual ~parent() {}
			};
		

	
}}}}

#endif





