#ifndef PHYSX_GAME_GAME_BASE_HPP
#define PHYSX_GAME_GAME_BASE_HPP

#include <neb/core/itf/shared.hpp>
#include <neb/core/game/game/base.hpp>

#include <neb/phx/game/ai/util/parent.hpp>

namespace neb { namespace phx { namespace game { namespace game {

	class base:
		virtual public neb::game::game::base,
		virtual public neb::phx::game::ai::util::parent
	{
		public:

			virtual void		init() {}
			virtual void		release() {}
			virtual void		step(gal::etc::timestep const & ts);


	};

}}}}

#endif
