#ifndef __GRU_GAME_GAME_UTIL_PARENT_HPP__
#define __GRU_GAME_GAME_UTIL_PARENT_HPP__

#include <map>


#include <Galaxy-Standard/shared.hpp>

#include <neb/game/game/base.hpp>

namespace neb { namespace game { namespace game { namespace util {


	/** @brief parent
	 */
	class parent:
		virtual public neb::util::parent<neb::game::game::base>
	{
		public:
			parent() {}
			virtual ~parent() {}

			virtual void						init() {}
	};



}}}}

#endif

