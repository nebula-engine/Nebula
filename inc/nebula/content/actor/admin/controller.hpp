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
					virtual	void								init(const boost::shared_ptr<nebula::content::scene::admin::base>&);
					/// shutdown
					virtual	void								shutdown();
					/// update
					virtual	void								update();
					/// step
					virtual	void								step();
					/// render
					virtual	void								render(const boost::shared_ptr<nebula::platform::renderer::base>&);
				
				
				
				
					/// create shapes
					virtual	void								create_shape();
	
					/// lookat
					virtual void								lookat(const boost::shared_ptr<nebula::platform::renderer::base>&);
					
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

				};
			}
		}
	}
}

#endif








