#ifndef __GRU_GAME_TRIGGER_UTIL_PARENT_HPP__
#define __GRU_GAME_TRIGGER_UTIL_PARENT_HPP__

#include <map>

#include <gal/itf/shared.hpp>

#include <neb/core/util/parent.hpp>
#include <neb/core/game/trigger/base.hpp>

namespace neb { namespace game { namespace trigger { namespace util {
	/** @brief @Parent
	 * abstract class for parent of an @Actor
	 */
	class parent:
<<<<<<< HEAD
		virtual public neb::util::parent<neb::game::trigger::base>
	{
		public:
			parent() {}
			virtual ~parent() {}

=======
		virtual public neb::util::parent<neb::game::trigger::base, parent>
	{
		public:
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
			virtual void						init() {}
	};
}}}}

#endif

