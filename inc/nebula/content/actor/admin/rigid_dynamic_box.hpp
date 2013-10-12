#ifndef __NEBULA_CONTENT_ACTOR_ADMIN_RIGID_DYNAMIC_BOX_HPP__
#define __NEBULA_CONTENT_ACTOR_ADMIN_RIGID_DYNAMIC_BOX_HPP__

#include <nebula/content/actor/admin/rigid_dynamic.hpp>

#include <nebula/ns.hpp>

namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace admin
			{
				/// rigid dynamic
				class rigid_dynamic_box:
					public n34100::rigid_dynamic
				{
				public:
					///@name ctor and dtor
					///@{
					// Ctor
					rigid_dynamic_box();
					/// Copy Ctor
					rigid_dynamic_box(const rigid_dynamic_box&);
					/// Dtor
					~rigid_dynamic_box();
					///@}

					///@name operator
					///@{
					/// assignment
					rigid_dynamic_box&							operator=(const rigid_dynamic_box&);
					///@}

				

					/// init
					virtual	void								init( jess::shared_ptr<n32100::base> );
					/// shutdown
					virtual	void								shutdown();
					/// update
					virtual	void								update();
					/// step
					virtual	void								step();
					/// render
					virtual	void								render( jess::shared_ptr<nebula::platform::renderer::base> );
				
				
				
				
					/// create shapes
					virtual	void								create_shapes();




					jess::shared_ptr<n35100::box>						box_;


					float x_;
					float y_;
					float z_;
				};
			}
		}
	}
}

#endif








