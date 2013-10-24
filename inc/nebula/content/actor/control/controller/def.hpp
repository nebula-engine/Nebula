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
					class def:
						public n34000::control::controller::base
					{
						friend class n34100::controller::base;
						protected:
						/** \brief copy ctor
						 */
						def( def const & ) = default;
						/** \brief assignment
						 */
						def&				operator=( def const & );
						/** \brief ctor
						 */
						def( jess::shared_ptr<n34100::controller::base> );
						public:
						/** \brief dtor
						 */
						virtual ~def();
						/** \brief init
						 */
						virtual void					init();
						/** \brief event
						 */
						virtual void					process_event( int );
						/** \brief connect
						 */
						virtual void					connect_to_window( jess::shared_ptr<n22000::base> );

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
						virtual bool					on_key_down( int );
						/** \brief key up
						 */
						virtual bool					on_key_up( int );
						/** \brief pointer motion
						 */
						virtual bool					on_pointer_motion( int, int );
						///@}
						std::shared_ptr< jess::signal::connection<int> >	connection_key_down_;
						std::shared_ptr< jess::signal::connection<int> >	connection_key_up_;
						std::shared_ptr< jess::signal::connection<int,int> >	connection_pointer_motion_;
					};
				}
			}
		}
	}
}

#endif
