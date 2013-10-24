#ifndef __NEBULA_CONTENT_ACTOR_CONTROL_CONTROLLER_BASE_HPP__
#define __NEBULA_CONTENT_ACTOR_CONTROL_CONTROLLER_BASE_HPP__

#include <map>

#include <nebula/define.hpp>

#include <jess/shared_ptr.hpp>

#include <PxPhysicsAPI.h>

#include <nebula/ns.hpp>

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
					/** \brief %control
					 */
					class base
					{
						public:
							/** \brief flag
							 */
							struct flag
							{
								/** \brief enum
								 */
								enum e
								{
									eNORTH = 1 << 0,
									eSOUTH = 1 << 1,
									eEAST  = 1 << 2,
									eWEST  = 1 << 3
								};
							};
							/** \brief event
							 */
							struct event
							{
								/** \brief enum
								 */
								enum
								{
									eINVALID = 0,
									eRESET_VIEW_ANGLES
								};
							};
						protected:
							/** \brief copy ctor
							 */
							base( base const & ) = default;
							/** \brief assignment
							 */
							base&						operator=( base const & ) = default;
							/** \brief ctor
							 */
							base( jess::shared_ptr<n34100::controller::base> );
						public:
							/** \brief dtor
							 */
							virtual ~base();
							/** \brief init
							 */
							virtual void					init() = 0;
							/** \breif connect
							 */
							virtual void					connect_to_window( jess::shared_ptr<n22000::base> ) = 0;
							/** \brief is valid
							 */
							virtual bool					is_valid() = 0;
							/** \brief move
							 */
							virtual physx::PxVec3				move() = 0;
							/** process event
							 */
							virtual void					process_event( int ) = 0;
							/** @name on
							 */
							///@{
							/** \brief key down
							 */
							virtual bool					on_key_down( int ) = 0;
							/** \brief key up
							 */
							virtual bool					on_key_up( int ) = 0;
							/** \brief pointer motion
							 */
							virtual bool					on_pointer_motion( int, int ) = 0;
							///@}
							/** \brief window
							 */
							jess::shared_ptr<n22000::base>			window_;
							/** \brief flag
							 */
							unsigned int					flag_;
							/** key flag
							 */
							std::map<int,unsigned int>			key_flag_;
							/** key up
							 */
							std::map<int,int>				key_up_event_;
							/** key down
							 */
							std::map<int,int>				key_down_event_;
							/** \brief parent
							 */
							std::weak_ptr<n34100::controller::base>		parent_;
							/** \brief head
							 */
							std::map<int,physx::PxVec3>			head_;
							/** \brief head flag
							 */
							std::map<unsigned int,int>			head_flag_;
					};
				}
			}
		}
	}
}

#endif
