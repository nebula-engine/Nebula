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
				/** controller
				 */
				namespace controller
				{
					class base:
						public n34100::base
					{
						friend class n30000::base;
						friend class n32100::base;
						friend class n34000::control::controller::base;
						friend class n34000::control::controller::def;
						friend class n34200::controller;
						friend class n34300::controller;
						public:

						protected:
						/// copy ctor
						base(const base&);
						/// assignment
						base&								operator=(const base&);
						/// ctor
						base( jess::shared_ptr<n32100::base> );
						public:
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
						jess::shared_ptr<n34000::control::controller::base>			control_;

					};
				}
			}
		}
	}
}


#endif








