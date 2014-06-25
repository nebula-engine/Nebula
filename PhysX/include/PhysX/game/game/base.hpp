#ifndef PHYSX_GAME_GAME_BASE_HPP
#define PHYSX_GAME_GAME_BASE_HPP

#include <neb/util/shared.hpp>
#include <neb/game/game/base.hpp>

#include <PhysX/game/ai/util/parent.hpp>

namespace phx { namespace game { namespace game {

	class base:
		virtual public neb::game::game::base,
		virtual public phx::game::ai::util::parent
	{
		public:

			virtual void		init() {}
			virtual void		release() {}
			virtual void		step(gal::std::timestep const & ts);


	};

}}}

#endif
