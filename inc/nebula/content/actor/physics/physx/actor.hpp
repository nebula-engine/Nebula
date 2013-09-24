#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_PHYSX_ACTOR_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_PHYSX_ACTOR_HPP__

#include <nebula/content/actor/physics/physx/base.hpp>

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
					public nebula::content::actor::admin::base
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
					virtual	void								init(const boost::shared_ptr<nebula::content::scene::admin::base>&);
					/// shutdown
					virtual	void								shutdown();
					/// update
					virtual	void								update();
					/// step
					virtual	void								step();
					/// render
					virtual	void								render(const boost::shared_ptr<nebula::platform::renderer::base>&);
					
					
					
					/// px actor
					boost::shared_ptr< ::physx::PxActor>					px_actor_;
				};
			}
			}
		}
	}
}

#endif








