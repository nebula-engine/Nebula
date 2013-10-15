#ifndef __CONTENT_ANIMATION_FRAME_H__
#define __CONTENT_ANIMATION_FRAME_H__

#include <vector>

#include <nebula/ns.hpp>

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
				virtual	void						step( float );
				/// Add Child
				void							AddChild( frame* );
				/// Add Actor
				void							AddActor(nebula::content::actor::admin::base*);


				///
				void							(*m_func)( physx::PxVec3 );
				
				/// Parent
				nebula::content::animation::frame*			m_parent;

				/// Children
				std::vector<n30000::animation::frame*>		m_children;

				/// Actors
				std::vector<n34100::base*>	m_actors;

				/// pose
				physx::PxMat44						pose_;

			};

			class translation: public frame
			{
				/// ctor
				translation( physx::PxVec3 );
				/// step
				void					step( float );
				/// rate
				physx::PxVec3				rate_;
			};
		}
	}
}




#endif
