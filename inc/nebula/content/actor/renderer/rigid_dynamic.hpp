#ifndef __NEBULA_CONTENT_ACTOR_RENDERER_RIGID_DYNAMIC_HPP__
#define __NEBULA_CONTENT_ACTOR_RENDERER_RIGID_DYNAMIC_HPP__



#include <nebula/content/actor/renderer/rigid_body.hpp>

namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace renderer
			{
				/// rigid dynamic
				class rigid_dynamic:
					public n34300::rigid_body
				{
					public:
						// Ctor
						rigid_dynamic( std::shared_ptr<n34100::base> );
						/// Copy Ctor
						rigid_dynamic(const rigid_dynamic&);
						/// Dtor
						~rigid_dynamic();
						/// assignment
						rigid_dynamic&								operator=(const rigid_dynamic&);
						/// init
						virtual	void								init();
						/// shutdown
						virtual	void								shutdown();
						/// update
						virtual	void								update();
						/// step
						virtual	void								step(float);
						/// render
						virtual	void								render( std::shared_ptr<n23000::base> );
						/// create shapes
						virtual	void								create_shapes();
				};
			}
		}
	}
}

#endif








