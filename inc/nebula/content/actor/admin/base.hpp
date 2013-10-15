#ifndef __NEBULA_CONTENT_ACTOR_ADMIN_BASE_HPP__
#define __NEBULA_CONTENT_ACTOR_ADMIN_BASE_HPP__

#include <nebula/define.hpp>
#include <PxPhysicsAPI.h>

#include <jess/shared_ptr.hpp>
#include <jess/map.hpp>

#include <nebula/ns.hpp>

namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace admin
			{
				/// base
				class base:
					public jess::enable_shared_from_this<n34100::base>
				{
					protected:
						/// copy ctor
						base(const base&);
						/// assignment
						base&									operator=(const base&);
					public:
						/// ctor
						base( jess::shared_ptr<n32100::base> );
						/// dtor
						virtual ~base();
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
						/// physics material
						virtual jess::shared_ptr<n34200::material>				create_physics_material();
						/// create shapes
						virtual	void								create_shapes();
						/// get pose
						physx::PxMat44								get_pose();
						/// set pose
						void									set_pose( physx::PxMat44 );
						/// parent
						std::weak_ptr<n32100::base>						parent_;
						/// physics
						jess::shared_ptr<n34200::base>						physics_;
						/// renderer
						jess::shared_ptr<n34300::base>						renderer_;
						/// materials
						jess::map<n34100::material>			materials_;
						/// flag
						int									flag_;
						/// pose
						physx::PxMat44								pose_;
						/// velocity
						physx::PxVec3								velocity_;
				};
			}
		}
	}
}

#endif








