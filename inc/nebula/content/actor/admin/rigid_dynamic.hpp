#ifndef __NEBULA_CONTENT_ACTOR_ADMIN_RIGID_DYNAMIC_HPP__
#define __NEBULA_CONTENT_ACTOR_ADMIN_RIGID_DYNAMIC_HPP__



#include <nebula/content/actor/admin/rigid_body.hpp>

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
				class rigid_dynamic:
					public n34100::rigid_body
				{
					protected:
						/// copy ctor
						rigid_dynamic(const rigid_dynamic&);
						/// assignment
						rigid_dynamic&								operator=(const rigid_dynamic&);
					public:			
						/// ctor
						rigid_dynamic( jess::shared_ptr<n32100::base> );
						/// dtor
						~rigid_dynamic();
						/// init
						virtual	void								init();
						/// shutdown
						virtual	void								shutdown();
						/// update
						virtual	void								update();
						/// step
						virtual	void								step( float );
						/// render
						virtual	void								render( jess::shared_ptr<n23000::base> );
						/// create shapes
						virtual	void								create_shapes();
				};
			}
		}
	}
}


#endif








