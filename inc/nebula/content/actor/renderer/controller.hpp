#ifndef __NEBULA_CONTENT_ACTOR_RENDERER_CONTROLLER_HPP__
#define __NEBULA_CONTENT_ACTOR_RENDERER_CONTROLLER_HPP__



#include <nebula/content/actor/renderer/base.hpp>

namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace renderer
			{
				/// controller
				class controller:
					public n34300::base
				{
				public:
					///@name ctor and dtor
					///@{
					// Ctor
					controller();
					/// Copy Ctor
					controller(const controller&);
					/// Dtor
					~controller();
					///@}

					///@name operator
					///@{
					/// assignment
					controller&								operator=(const controller&);
					///@}

				

					/// init
					virtual	void								init( jess::shared_ptr<n34100::base> );
					/// shutdown
					virtual	void								shutdown();
					/// update
					virtual	void								update();
					/// step
					virtual	void								step( float );
					/// render
					virtual	void								render( jess::shared_ptr<nebula::platform::renderer::base> );
				
				
				
				
					/// create shapes
					virtual	void								create_shapes();
				};
			}
		}
	}
}

#endif








