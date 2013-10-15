#ifndef __NEBULA_CONTENT_ACTOR_ADMIN_CONTROLLER_CONTROL_HPP__
#define __NEBULA_CONTENT_ACTOR_ADMIN_CONTROLLER_CONTROL_HPP__

namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace admin
			{
				namespace controller
				{
					/** \brief %control
					*/
					class control
					{
						friend class n34100::controller;
						protected:
						/** \brief copy ctor
						*/
						control( control const & );
						/** \brief assignment
						*/
						control&			operator=( control const & );
						/** \brief ctor
						*/
						control( jess::shared_ptr<n34100::controller> );
						public:
						/** \brief dtor
						*/
						~control();
						/** \brief move
						*/
						virtual physx::PxVec3		move();
						/** @name on
						*/
						///@{
						/** \brief key down
						*/
						virtual bool			on_key_down( int ) = 0;
						/** \brief key up
						*/
						virtual bool			on_key_up( int ) = 0;
						/** \brief pointer motion
						*/
						virtual bool			on_pointer_motion( int ) = 0;
						///@}
					};
				}
			}
		}
	}
}

#endif
