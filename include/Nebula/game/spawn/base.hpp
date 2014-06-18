#ifndef NEBULA_GAME_SPAWN_BASE_HPP
#define NEBULA_GAME_SPAWN_BASE_HPP

#include <Nebula/Core/pose.hpp>

namespace neb { namespace game { namespace spawn {

	class base: virtual public neb::std::shared {
		public:

			neb::core::pose		pose_;

			
	};

	
}}}

#endif
