#ifndef __NEBULA_CONTENT_ACTOR_ADMIN_CONTROLLER_CONTROL_HPP__
#define __NEBULA_CONTENT_ACTOR_ADMIN_CONTROLLER_CONTROL_HPP__

#include <nebula/ns.hpp>

#include <nebula/content/actor/control/controller/base.hpp>

namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace control
			{
				namespace controller
				{
					/** \brief %control %default
					 */
					class default_control:
						public n34000::control::controller::base
					{
						friend class n34100::controller::base;
						protected:
						/** \brief copy ctor
						 */
						default_control( default_control const & ) = default;
						/** \brief assignment
						 */
						default_control&				operator=( default_control const & );
						/** \brief ctor
						 */
						default_control( jess::shared_ptr<n34100::controller::base> );
						public:
						/** \brief dtor
						 */
						virtual ~default_control();
						/** \brief init
						 */
						virtual void					init();
						/** \brief connect to window
						 */
						virtual void					connect_to_window( jess::shared_ptr<n22000::base> window );
						/** \brief is valid
						 */
						virtual bool					is_valid();
						/** \brief move
						 */
						virtual physx::PxVec3				move();
						/** @name on
						 */
						///@{
						/** \brief key down
						 */
						virtual bool					on_key_down( int, int );
						/** \brief key up
						 */
						virtual bool					on_key_up( int, int );
						/** \brief pointer motion
						 */
						virtual bool					on_pointer_motion( int , int );
						///@}
					};
				}
			}
		}
	}
}

#endif
