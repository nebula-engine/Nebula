#ifndef __NEBULA_CONTENT_ACTOR_RENDERER_VEHICLE_HPP__
#define __NEBULA_CONTENT_ACTOR_RENDERER_VEHICLE_HPP__



#include <nebula/content/actor/renderer/base.hpp>

namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace renderer
			{
				/// rigid dynamic
				class vehicle:
					public n34300::base
				{
				public:
					///@name ctor and dtor
					///@{
					// Ctor
					vehicle();
					/// Copy Ctor
					vehicle(const vehicle&);
					/// Dtor
					~vehicle();
					///@}

					///@name operator
					///@{
					/// assignment
					vehicle&								operator=(const vehicle&);
					///@}
					
					

					/// init
					virtual	void								init( jess::shared_ptr<n34100::base>);
					/// shutdown
					virtual	void								shutdown();
					/// update
					virtual	void								update();
					/// step
					virtual	void								step();
					/// render
					virtual	void								render( jess::shared_ptr<n23000::base>);
				
				
				
				};
			}
		}
	}
}


#endif








