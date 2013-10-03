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
				public ncar::rigid_body
			{
			public:
				///@name ctor and dtor
				///@{
				// Ctor
				rigid_dynamic();
				/// Copy Ctor
				rigid_dynamic(const rigid_dynamic&);
				/// Dtor
				~rigid_dynamic();
				///@}

				///@name operator
				///@{
				/// assignment
				rigid_dynamic&								operator=(const rigid_dynamic&);
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
				
				
				
				
				/// create shapes
				virtual	void								create_shapes();
			};
		};
	};
};
}
#endif








