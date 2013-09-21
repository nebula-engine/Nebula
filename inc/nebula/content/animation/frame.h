#ifndef __CONTENT_ANIMATION_FRAME_H__
#define __CONTENT_ANIMATION_FRAME_H__

#include <vector>



namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace admin
			{
				class base;
			}
		}
	}
}


namespace nebula
{
	namespace content
	{
		namespace animation
		{
			class frame
			{
			public:
			
			
				/// Step
				virtual	void						Step( FLOAT );
				/// Add Child
				void							AddChild( frame* );
				/// Add Actor
				void							AddActor(nebula::content::actor::admin::base*);


				///
				void							(*m_func)(boost::numeric::ublas::vector<FLOAT>&);

				/// Parent
				nebula::content::animation::frame*			m_parent;

				/// Children
				std::vector<nebula::content::animation::frame*>		m_children;

				/// Actors
				std::vector<nebula::content::actor::admin::base*>	m_actors;

				/// pose
				boost::numeric::ublas::matrix<FLOAT>			m_pose;

			};

			class translation: public frame
			{
				/// ctor
									translation(boost::numeric::ublas::vector<FLOAT>&);
				/// step
				void					Step(FLOAT);
				/// rate
				boost::numeric::ublas::vector<FLOAT>	m_rate;
			};
		}
	}
}




#endif
