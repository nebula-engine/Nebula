#ifndef __NEBULA_CONTENT_ACTOR_RENDERER_RIGID_ACTOR_HPP__
#define __NEBULA_CONTENT_ACTOR_RENDERER_RIGID_ACTOR_HPP__



#include <nebula/content/actor/renderer/actor.hpp>

namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace renderer
			{
				/// rigid dynamic
				class rigid_actor:
					public ncar::actor
				{
				public:
					///@name ctor and dtor
					///@{
					// Ctor
					rigid_actor();
					/// Copy Ctor
					rigid_actor(const rigid_actor&);
					/// Dtor
					~rigid_actor();
					///@}

					///@name operator
					///@{
					/// assignment
					rigid_actor&								operator=(const rigid_actor&);
					///@}

				

					/// init
					virtual	void								init(const jess::shared_ptr<ncaa::base>&);
					/// shutdown
					virtual	void								shutdown();
					/// update
					virtual	void								update();
					/// step
					virtual	void								step(FLOAT);
					/// render
					virtual	void								render(const jess::shared_ptr<nebula::platform::renderer::base>&);
				
				
				
				
					/// create shapes
					virtual	void								create_shapes();
				};
			}
		}
	}
}

#endif








