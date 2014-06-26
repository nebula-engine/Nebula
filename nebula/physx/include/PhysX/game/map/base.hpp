#ifndef PHYSX_GAME_MAP_HPP
#define PHYSX_GAME_MAP_HPP


#include <neb/core/game/map/base.hpp>

#include <PhysX/core/scene/util/decl.hpp>
#include <PhysX/core/scene/local.hpp>

namespace phx { namespace game { namespace map {

	class base:
		virtual public phx::core::scene::local,
		virtual public neb::game::map::base
	{
		public:
			base(sp::shared_ptr<phx::core::scene::util::parent> parent);

			virtual void			init();
			virtual void			release();
	};



}}}


#endif

