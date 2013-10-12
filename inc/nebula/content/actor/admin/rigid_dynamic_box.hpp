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
					protected:
						/// copy ctor
						rigid_dynamic_box(const rigid_dynamic_box&);
						/// assignment
						rigid_dynamic_box&							operator=(const rigid_dynamic_box&);
					public:
						/// ctor
						rigid_dynamic_box( jess::shared_ptr<n32100::base> );
						/// dtor
						~rigid_dynamic_box();
						/// init
						virtual	void								init();
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
						/// shape
						jess::shared_ptr<n35100::box>						box_;
						/// size
						physx::PxVec3								size_;
				};
			}
		}
	}
}

#endif








