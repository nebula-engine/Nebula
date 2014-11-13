#ifndef PHYSX_GAME_AI_UTIL_PARENT_HPP
#define PHYSX_GAME_AI_UTIL_PARENT_HPP


#include <neb/core/util/parent.hpp>

#include <neb/phx/game/ai/base.hpp>

namespace neb { namespace phx { namespace game { namespace ai { namespace util {



			/** @brief @Parent
			 * abstract class for parent of a shape
			 */
			class parent:
				virtual public neb::util::parent<phx::game::ai::base>
			{
				public:
					virtual ~parent() {}
			};
		

	
}}}}}

#endif





