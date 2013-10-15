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
					/** \brief %control %default
					*/
					class control_default:
						public n34100::controller::control
					{
						friend class n34100::controller;
						protected:
						/** \brief copy ctor
						*/
						control( control const & )
						{

						}
						/** \brief assignment
						*/
						control&			operator=( control const & )
						{
							return *this;
						}
						/** \brief ctor
						*/
						control( jess::shared_ptr<n34100::controller> );
						public:
						/** \brief dtor
						*/
						virtual ~control();
						/** \brief init
						*/
						virtual void			init();
						/** \brief is_valid()
						*/
						virtual bool			is_valid();
						/** \brief move
						*/
						virtual physx::PxVec3		move();
						/** @name on
						*/
						///@{
						/** \brief key down
						*/
						virtual bool			on_key_down( int, int );
						/** \brief key up
						*/
						virtual bool			on_key_up( int, int );
						/** \brief pointer motion
						*/
						virtual bool			on_pointer_motion( int , int );
						///@}
					};
				}
			}
		}
	}
}

#endif
