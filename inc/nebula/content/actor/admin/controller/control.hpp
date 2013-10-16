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
						~control();
						/** \brief init
						*/
						virtual void			init() = 0;
						/** \brief is valid
						*/
						virtual bool			is_valid() = 0;
						/** \brief move
						*/
						virtual physx::PxVec3		move() = 0;
						/** process event
						*/
						virtual void			process_event( int ) = 0;
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
						/** key flag
						*/
						std::map<int,unsigned int>	key_flag_;
						/** key up
						*/
						std::map<int,int>		key_up_event_;
						/** key down
						*/
						std::map<int,int>		key_down_event_;
						/** \brief parent
						 */
						jess::shared_ptr<n34100::controller>		parent;
					};
				}
			}
		}
	}
}

#endif
