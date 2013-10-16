#ifndef __NEBULA_CONTENT_ACTOR_ADMIN_CONTROLLER_HPP__
#define __NEBULA_CONTENT_ACTOR_ADMIN_CONTROLLER_HPP__

#include <nebula/ns.hpp>

#include <nebula/content/actor/admin/base.hpp>

namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace admin
			{
				/// controller
				class controller:
					public n34100::base
				{
					friend class n34100::controller::control;
					public:
						
					protected:
						/// copy ctor
						controller(const controller&);
						/// assignment
						controller&								operator=(const controller&);
						/// ctor
						controller( jess::shared_ptr<n32100::base> );
					public:
						/// dtor
						virtual ~controller();
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
						/// lookat
						virtual void								look_at( jess::shared_ptr<n23000::base> );
					protected:
						/// pos
						physx::PxVec3								pos_;
						/// look
						physx::PxVec3								look_;
						/// up
						physx::PxVec3								up_;
						/// yaw
						float									yaw_;
						/// pitch
						float									pitch_;
						/** \brief control
						*/
						jess::shared_ptr<n34100::controller::control>				control_;
						
				};
			}
		}
	}
}



#endif








