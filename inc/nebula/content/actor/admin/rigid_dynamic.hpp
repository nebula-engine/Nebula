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
				virtual	void								init( jess::shared_ptr<nebula::content::scene::admin::base> );
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








