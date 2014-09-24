#ifndef NEBULA_EXT_MAZE_GAME_MAP_MAZE2_HPP
#define NEBULA_EXT_MAZE_GAME_MAP_MAZE2_HPP

#include <neb/core/game/map/base.hpp>

#include <neb/phx/game/map/base.hpp>

#include <neb/fin/gfx_phx/core/scene/base.hpp>

namespace neb {
	namespace ext {
		namespace maze {
			namespace game {
				namespace map {
					/** @brief maze
					 *
					 */
					class maze2:
						virtual public neb::game::map::base,
						virtual public neb::phx::game::map::base,
						virtual public neb::fin::gfx_phx::core::scene::base
					{
						public:
							maze2(
									shared_ptr<neb::fin::gfx_phx::core::scene::util::parent> parent,
									ivec2 size);
							virtual void		init();
							virtual void		release();
							ivec2			size_;
					};
				}
			}
		}
	}
}

#endif

