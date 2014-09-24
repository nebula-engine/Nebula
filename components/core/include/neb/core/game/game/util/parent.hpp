#ifndef __GRU_GAME_GAME_UTIL_PARENT_HPP__
#define __GRU_GAME_GAME_UTIL_PARENT_HPP__

#include <gal/itf/shared.hpp>

#include <neb/core/game/game/base.hpp>

namespace neb { namespace game { namespace game { namespace util {


	/** @brief parent
	 */
	class parent:
<<<<<<< HEAD
		virtual public neb::util::parent<neb::game::game::base>
=======
		virtual public neb::util::parent<neb::game::game::base, parent>
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
	{
		public:
			parent() {}
			virtual ~parent() {}
		protected:
<<<<<<< HEAD
			virtual void				__init() {}
=======
			virtual void						__init();
		public:
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
	};



}}}}

#endif

