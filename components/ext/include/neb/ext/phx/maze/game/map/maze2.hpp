#ifndef PHYSX_EXT_MAZE_GAME_MAP_MAZE2_HPP
#define PHYSX_EXT_MAZE_GAME_MAP_MAZE2_HPP

#include <neb/ext/maze/game/map/maze2.hpp>

#include <PhysX/game/map/base.hpp>

namespace phx { namespace ext { namespace maze { namespace game { namespace map {

	class maze2:
		virtual public neb::ext::maze::game::map::maze2,
		virtual public phx::game::map::base
	{
		public:
			maze2(
					std::shared_ptr<phx::core::scene::util::parent> parent,
					ivec2 size);

			virtual void		init();
	};



}}}}}


#endif

