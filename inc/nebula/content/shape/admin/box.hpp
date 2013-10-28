#ifndef __NEBULA_CONTENT_SHAPE_ADMIN_BOX_HPP__
#define __NEBULA_CONTENT_SHAPE_ADMIN_BOX_HPP__

//#include <enable_shared_from_this>

#include <nebula/content/shape/admin/base.hpp>

#include <nebula/ns.hpp>

namespace nebula
{
	namespace content
	{
		namespace shape
		{
			namespace admin
			{
				/// box
				class box:
					public nebula::content::shape::admin::base
				{
					protected:
						/// copy ctor
						box( box const & ) = default;
						/// assignment
						box&								operator=( box const & ) = default;
					public:
						/// ctor
						box( std::shared_ptr<n34100::rigid_actor> );
						/// init
						void								init();
						/// shutdown
						void								shutdown();
						/// render
						void								render( jess::shared_ptr<n23000::base> );
						/// get pose
						physx::PxMat44							get_pose()
						{
							return pose_;
						}
				};
			}
		}
	}
}


#endif
