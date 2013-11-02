#ifndef __NEBULA_CONTENT_SHAPE_ADMIN_PLANE_HPP__
#define __NEBULA_CONTENT_SHAPE_ADMIN_PLANE_HPP__

#include <nebula/content/shape/admin/base.hpp>

namespace nebula
{
	namespace content
	{
		namespace shape
		{
			namespace admin
			{
				class plane:
					public n35100::base
				{
					public:
						/// ctor
						plane( std::shared_ptr<n34100::rigid_actor> );
						/// init
						virtual void					init();
						/// shutdown
						virtual void					shutdown();
						/// render
						virtual void					render( std::shared_ptr<n23000::base> );

				};
			}
		}
	}
}

#endif
