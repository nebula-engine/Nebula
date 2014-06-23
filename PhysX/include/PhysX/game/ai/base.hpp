#ifndef PHYSX_GAME_AI_BASE_HPP
#define PHYSX_GAME_AI_BASE_HPP

#include <gal/std/timestep.hpp>

#include <Nebula/util/shared.hpp>

#include <PhysX/core/actor/util/decl.hpp>

namespace phx { namespace game { namespace ai {


	class base:
		virtual public neb::std::shared
	{
		public:

			void						step(gal::std::timestep const & ts);
		public:
			sp::weak_ptr<phx::core::actor::base>		actor_;
			/** @brief target
			 */
			sp::weak_ptr<phx::core::actor::base>		target_;



	};


}}}

#endif

