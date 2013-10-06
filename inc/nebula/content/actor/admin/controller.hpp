#ifndef __NEBULA_CONTENT_ACTOR_ADMIN_CONTROLLER_HPP__
#define __NEBULA_CONTENT_ACTOR_ADMIN_CONTROLLER_HPP__

#include <boost/numeric/ublas/vector.hpp>

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
					public nebula::content::actor::admin::base
				{
				public:
					/// flag
					struct flag
					{
						/// enum
						enum e
						{
							eNORTH,
							eSOUTH,
							eEAST,
							eWEST
						};
					};
					/// event
					struct event
					{
						/// enum
						enum
						{
							eRESET_VIEW_ANGLES
};
};
					/// handler key down
					void							handle_key_down(int,int);
					
					/// handler key up
					void							handle_key_up(int,int);
					
					/// handler pointer motion
					void							handle_pointer_motion(int,int);
					
					
					///@name ctor and dtor
					///@{
					// Ctor
					controller();
					/// Copy Ctor
					controller(const controller&);
					/// Dtor
					~controller();
					///@}

					///@name operator
					///@{
					/// assignment
					controller&								operator=(const controller&);
					///@}
					
					
					
					/// init
					virtual	void								init( jess::shared_ptr<nebula::content::scene::admin::base>&);
					/// shutdown
					virtual	void								shutdown();
					/// update
					virtual	void								update();
					/// step
					virtual	void								step(FLOAT);
					/// render
					virtual	void								render(const jess::shared_ptr<nebula::platform::renderer::base>&);
					
					
					

					virtual void								process_event(int);
					







					
					/// create shapes
					virtual	void								create_shapes();
					
					/// lookat
					virtual void								look_at(const jess::shared_ptr<nebula::platform::renderer::base>&);
					
					/// get move
					boost::numeric::ublas::vector<FLOAT>					get_move();
					
					/// move
					boost::numeric::ublas::vector<FLOAT>					move_;
					/// pos
					boost::numeric::ublas::vector<FLOAT>					pos_;
					/// look
					boost::numeric::ublas::vector<FLOAT>					look_;
					/// up
					boost::numeric::ublas::vector<FLOAT>					up_;
					
					
					
					FLOAT yaw_;
					FLOAT pitch_;
			
					std::map<int,int>							key_flag_;
					std::map<int,int>							key_up_event_;
					std::map<int,int>							key_down_event_;



	
				};
			}
		}
	}
}



#endif








