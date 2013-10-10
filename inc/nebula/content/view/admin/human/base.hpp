#ifndef __NEBULA_CONTENT_VIEW_ADMIN_HUMAN_BASE_HPP__
#define __NEBULA_CONTENT_VIEW_ADMIN_HUMAN_BASE_HPP__

#include <jess/shared_ptr.hpp>

#include <nebula/content/view/admin/base.hpp>

namespace nebula
{
	namespace content
	{
		namespace view
		{
			namespace admin
			{
				namespace human
				{
					class base:
						public ncva::base
					{
						public:
							/// ctor
							base();
							/// dtor
							virtual ~base();
							/// init
							virtual void					init( jess::shared_ptr<nc_sc_a::base> );

							virtual void					shutdown();

							virtual void					update();

							virtual void					render();

							virtual void					create_camera();
					};
				}
			}
		}
	}
}

#endif
