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
					public n34300::rigid_actor
				{
				public:
					// Ctor
					rigid_body( std::shared_ptr<n34100::base> );
					/// Copy Ctor
					rigid_body(const rigid_body&);
					/// Dtor
					~rigid_body();
					/// assignment
					rigid_body&								operator=(const rigid_body&);
					/// init
					virtual	void								init();
					/// shutdown
					virtual	void								shutdown();
					/// update
					virtual	void								update();
					/// step
					virtual	void								step( float );
					/// render
					virtual	void								render( std::shared_ptr<n23000::base> );
				};
			}
		}
	}
}

#endif








