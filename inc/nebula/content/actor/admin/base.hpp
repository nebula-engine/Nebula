#ifndef __NEBULA_CONTENT_ACTOR_ADMIN_BASE_HPP__
#define __NEBULA_CONTENT_ACTOR_ADMIN_BASE_HPP__

#include <boost/shared_ptr.hpp>
#include <boost/numeric/ublas/matrix.hpp>

#include <jess/shared_ptr.hpp>
#include <jess/map.hpp>

#include <nebula/utilities/types/platform/types.hpp>
#include <nebula/utilities/types/content/actor/types.hpp>
#include <nebula/utilities/types/content/scene/types.hpp>


namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace admin
			{
				/// rigid dynamic
				class base
				{
				public:
					///@name ctor and dtor
					///@{
					// Ctor
					base();
					/// Copy Ctor
					base(const rigid_body&);
					/// Dtor
					~base();
					///@}
	
					///@name operator
					///@{
					/// assignment
					base&									operator=(const base&);
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
					
					/// get pose
					boost::numeric::ublas::matrix<FLOAT>					get_pose();
					
					
					/// physics
					jess::shared_ptr<nebula::content::actor::physics::rigid_actor>		physics_;
					
					/// materials
					jess::map<nebula::content::actor::admin::material>			materials_;
					
					/// flag
					int									flag_;
					
					/// pose
					boost::numeric::ublas::matrix<FLOAT>					pose_;
				};
			}
		}
	}
}

#endif








