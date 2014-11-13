#ifndef __GRU_GAME_SPAWN_UTIL_PARENT_H__
#define __GRU_GAME_SPAWN_UTIL_PARENT_H__

#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <gal/itf/shared.hpp>

#include <neb/core/game/spawn/base.hpp>

namespace neb { namespace game { namespace spawn { namespace util {


	/** @brief @Parent
	 * abstract class for parent of an @Actor
	 */
	class parent:
<<<<<<< HEAD
		virtual public neb::util::parent<neb::game::spawn::base>
=======
		virtual public neb::util::parent<neb::game::spawn::base, parent>
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
	{
		public:
			parent() {}
			virtual ~parent() {}

			virtual void						init() {}
	};



}}}}

#endif

