#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_ACTOR_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_ACTOR_HPP__

#include <PxPhysicsAPI.h>

#include <glutpp/actor/actor.h>

#include <neb/actor/Base.h>

namespace neb
{
	namespace actor
	{
		class Actor:
			public neb::actor::Base
		{
			public:
				Actor(
						glutpp::actor::desc_shared,
						std::shared_ptr<neb::scene::scene>,
						neb::actor::Base_shared = neb::actor::Base_shared());


				virtual void			init();
				virtual void			release();
				virtual void			add_force() {abort();}
				virtual void			set_pose(math::transform);
				virtual int			fire();
				virtual glutpp::actor::desc_shared	get_projectile() {abort(); return NULL;}
				virtual glutpp::actor::desc_shared	get_desc();
				
				
				virtual void			create_physics() {abort();}
				virtual void			init_physics() {abort();}
				
				virtual void			step_remote(double);
				
				physx::PxActor*			px_actor_;
				
				//std::shared_ptr<glutpp::actor>		object_;
		};
	}
}

#endif


