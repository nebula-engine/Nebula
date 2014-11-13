#ifndef PHYSX_GAME_WEAPON_SIMPLE_PROJECTILE_HPP
#define PHYSX_GAME_WEAPON_SIMPLE_PROJECTILE_HPP

#include <neb/phx/game/weapon/base.hpp>

namespace neb { namespace phx { namespace game { namespace weapon {

	class SimpleProjectile: virtual public neb::phx::game::weapon::base {
		public:

			SimpleProjectile();
			
			virtual void					connect(std::shared_ptr<neb::gfx::window::base> window);
			virtual int					key_fun(std::shared_ptr<neb::gfx::window::base> window, int, int, int, int);
			virtual void					fire();
		
			double						size_;
			double						velocity_;
			double						damage_;

			weak_ptr<phx::core::actor::base>		actor_;

	};

}}}}

#endif
