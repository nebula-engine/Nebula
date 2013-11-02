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
						public:
							friend class n30000::base;
							friend class n32100::base;
							friend class n34200::controller;
							friend class n34300::controller;
							friend class n34400::controller::base;
							friend class n34400::controller::def;
						protected:
							/** \brief copy ctor
							*/
							base( base const & ) = default;
							/** \brief assignment
							*/
							base&							operator=( base const & ) = default;
							/** \brief ctor
							*/
							base( std::shared_ptr<n32100::base> );
						public:
							/** \brief dtor
							*/
							virtual ~base();
							/** \brief init
							*/
							virtual	void						init();
							/** \brief shutdown
							*/
							virtual	void						shutdown();
							/** \brief update
							*/
							virtual	void						update();
							/** \brief step
							*/
							virtual	void						step( float );
							/** \brief render
							*/
							virtual	void						render( std::shared_ptr<n23000::base> );
							/** \brief create shapes
							*/
							virtual	void						create_shapes();
							/** \brief lookat
							*/
							virtual void						look_at( std::shared_ptr<n23000::base> );
						protected:
							/** \brief pos
							*/
							physx::PxVec3						pos_;
							/** \brief look
							*/
							physx::PxVec3						look_;
							/** \brief up
							*/
							physx::PxVec3						up_;
							/** \brief yaw
							*/
							float							yaw_;
							/** \brief pitch
							*/
							float							pitch_;
							/** \brief velocity
							*/
							physx::PxVec3						velocity_;
							/** \brief control
							*/
							std::shared_ptr<n34400::controller::base>		control_;

					};
				}
			}
		}
	}
}


#endif








