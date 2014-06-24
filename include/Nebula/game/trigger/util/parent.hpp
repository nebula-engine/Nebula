#ifndef __GRU_GAME_TRIGGER_UTIL_PARENT_HPP__
#define __GRU_GAME_TRIGGER_UTIL_PARENT_HPP__

#include <map>


#include <Galaxy-Standard/shared.hpp>

#include <Nebula/util/parent.hpp>
#include <Nebula/game/trigger/base.hpp>

namespace neb { namespace game { namespace trigger { namespace util {


	/** @brief @Parent
	 * abstract class for parent of an @Actor
	 */
	class parent:
		virtual public neb::util::parent<neb::game::trigger::base>
	{
		public:
			parent() {}
			virtual ~parent() {}

			virtual void						init() {}
	};



}}}}

#endif

