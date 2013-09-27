#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_PHYSX_ACTOR_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_PHYSX_ACTOR_HPP__

#include <PxPhysicsAPI.h>

#include <nebula/content/actor/physics/actor.hpp>
#include <nebula/content/actor/physics/physx/base.hpp>

#include <nebula/ns.hpp>

namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace physics
			{
			namespace physx
			{
				/// rigid dynamic
				class actor:
					virtual public nebula::content::actor::physics::actor,
					virtual public nebula::content::actor::physics::physx::base
				{
				public:
					///@name ctor and dtor
					///@{
					// Ctor
					actor();
					/// Copy Ctor
					actor(const actor&);
					/// Dtor
					~actor();
					///@}

					///@name operator
					///@{
					/// assignment
					actor&									operator=(const actor&);
					///@}

				

					/// init
					virtual	void								init(const boost::shared_ptr<ncaa::base>&);
					/// shutdown
					virtual	void								shutdown();
					/// update
					virtual	void								update();
					/// step
					virtual	void								step(FLOAT);
					/// render
					virtual	void								render(const boost::shared_ptr<nebula::platform::renderer::base>&);
					
					/// set px_actor_
					void									set_px_actor(::physx::PxActor*);
					
					/// px actor
					::physx::PxActor*							px_actor_;
				};
			}
			}
		}
	}
}

#endif








