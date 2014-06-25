#ifndef NEBULA_EXT_MAZE_GAME_MAP_MAZE2_HPP
#define NEBULA_EXT_MAZE_GAME_MAP_MAZE2_HPP

#include <neb/game/map/base.hpp>

namespace neb { namespace ext { namespace maze { namespace game { namespace map {

	class maze2:
		virtual public neb::game::map::base
	{
		public:
			maze2(
					sp::shared_ptr<neb::core::scene::util::parent> parent,
					ivec2 size);


			virtual void		init();

			ivec2			size_;
	};



}}}}}


#endif

