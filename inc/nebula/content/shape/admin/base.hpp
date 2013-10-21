#ifndef __NEBULA_CONTENT_SHAPE_ADMIN_BASE_HPP__
#define __NEBULA_CONTENT_SHAPE_ADMIN_BASE_HPP__

#include <nebula/define.hpp>
#include <PxPhysicsAPI.h>

#include <jess/shared_ptr.hpp>

#include <nebula/ns.hpp>

namespace nebula
{
	namespace content
	{
		namespace shape
		{
			namespace admin
			{
				/// base	
				class base:
					public jess::enable_shared_from_this<n35100::base>
				{
					public:
						/// ctor	
						base();
						/// dtor					
						virtual ~base();
						/// init
						virtual void							init( jess::shared_ptr<n34100::rigid_actor> );
						/// shutdown
						virtual void							shutdown();
						/// render
						virtual void							render( jess::shared_ptr<n23000::base> );
						/// get pose
						physx::PxMat44							get_pose();
						/// get scale
						physx::PxVec3							get_scale();
						/// parent
						std::weak_ptr<n34100::rigid_actor>				parent_;
						/// renderer
						jess::shared_ptr<n35300::base>					renderer_;
						/// physics
						jess::shared_ptr<n35200::base>					physics_;
						/// pose
						physx::PxMat44							pose_;
						/// scale
						physx::PxVec3							scale_;
				};
			}
		}
	}
}


#endif
