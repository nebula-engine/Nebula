#ifndef __NEBULA_CONTENT_ACTOR_RENDERER_RIGID_BODY_HPP__
#define __NEBULA_CONTENT_ACTOR_RENDERER_RIGID_BODY_HPP__



#include <nebula/content/actor/renderer/rigid_actor.hpp>

namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace renderer
			{
				/// rigid dynamic
				class rigid_body:
					public ncar::rigid_actor
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
					virtual	void								init( jess::shared_ptr<ncaa::base> );
					/// shutdown
					virtual	void								shutdown();
					/// update
					virtual	void								update();
					/// step
					virtual	void								step( float );
					/// render
					virtual	void								render( jess::shared_ptr<nebula::platform::renderer::base> );
				
				
				
				
					
				};
			}
		}
	}
}

#endif








