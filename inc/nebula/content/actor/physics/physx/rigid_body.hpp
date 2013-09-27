#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_PHYSX_RIGID_BODY_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_PHYSX_RIGID_BODY_HPP__


#include <nebula/content/actor/physics/rigid_body.hpp>
#include <nebula/content/actor/physics/physx/rigid_actor.hpp>

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
				/// rigid body
				class rigid_body:
					virtual public ncapp::rigid_actor,
					virtual public ncap::rigid_body
				{
				public:
					///@name ctor and dtor
					///@{
					// Ctor
					rigid_body();
					/// Copy Ctor
					rigid_body(const rigid_body&);
					/// Dtor
					~rigid_body();
					///@}

					///@name operator
					///@{
					/// assignment
					rigid_body&								operator=(const rigid_body&);
					///@}

				

					/// init
					virtual	void								init(const boost::shared_ptr<ncaa::base>&);
					/// shutdown
					virtual	void								shutdown();
					/// update
					virtual	void								update();
					/// step
					virtual	void								step();
					/// render
					virtual	void								render(const boost::shared_ptr<nebula::platform::renderer::base>&);
				
							
					/// create shape
					virtual void								create_shape();
				};
			}
			}
		}
	}
}

#endif








