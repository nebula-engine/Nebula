#ifndef __NEBULA_CONTENT_ACTOR_ADMIN_CONTROLLER_HPP__
#define __NEBULA_CONTENT_ACTOR_ADMIN_CONTROLLER_HPP__

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
					public:
						/// flag
						struct flag
						{
							/// enum
							enum e
							{
								eNORTH = 1 << 0,
								eSOUTH = 1 << 1,
								eEAST  = 1 << 2,
								eWEST  = 1 << 3
							};
						};
						/// event
						struct event
						{
							/// enum
							enum
							{
								eINVALID = 0,
								eRESET_VIEW_ANGLES
							};
						};
					protected:
						/// copy ctor
						controller(const controller&);
						/// assignment
						controller&								operator=(const controller&);
					public:
						/// ctor
						controller( jess::shared_ptr<n32100::base> );
						/// dtor
						virtual ~controller();
						/// handler key down
						void									handle_key_down(int,int);
						/// handler key up
						void									handle_key_up(int,int);
						/// handler pointer motion
						void									handle_pointer_motion(int,int);
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
						/// process event
						virtual void								process_event(int);
						/// create shapes
						virtual	void								create_shapes();
						/// lookat
						virtual void								look_at( jess::shared_ptr<n23000::base> );
						/// get move
						physx::PxVec3								get_move();
					public:
						/// move
						physx::PxVec3								move_;
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
						/// key flag
						std::map<int,int>							key_flag_;
						/// key up
						std::map<int,int>							key_up_event_;
						/// key down
						std::map<int,int>							key_down_event_;
				};
			}
		}
	}
}



#endif








