#ifndef __NEBULA_CONTENT_ACTOR_ADMIN_BASE_HPP__
#define __NEBULA_CONTENT_ACTOR_ADMIN_BASE_HPP__

#include <boost/enable_shared_from_this.hpp>
#include <jess/shared_ptr.hpp>
#include <boost/numeric/ublas/matrix.hpp>

#include <jess/shared_ptr.hpp>
#include <jess/map.hpp>

#include <nebula/utilities/types/platform/types.hpp>
#include <nebula/utilities/types/content/actor/types.hpp>
#include <nebula/utilities/types/content/scene/types.hpp>

#include <nebula/ns.hpp>

namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace admin
			{
				/// rigid dynamic
				class base:
					public boost::enable_shared_from_this<ncaa::base>
				{
				public:
					///@name ctor and dtor
					///@{
					// Ctor
					base();
					/// Copy Ctor
					base(const base&);
					/// Dtor
					~base();
					///@}
	
					///@name operator
					///@{
					/// assignment
					base&									operator=(const base&);
					///@}
	
					
	
					/// init
					virtual	void								init(const jess::shared_ptr<nebula::content::scene::admin::base>&);
					/// shutdown
					virtual	void								shutdown();
					/// update
					virtual	void								update();
					/// step
					virtual	void								step( FLOAT dt );
					/// render
					virtual	void								render(const jess::shared_ptr<nebula::platform::renderer::base>&);
					
					
					
					
					/// create shapes
					virtual	void								create_shapes();
					
					/// get pose
					bnu::matrix<FLOAT>							get_pose();
					/// set pose
					void									set_pose(boost::numeric::ublas::matrix<FLOAT>);




					/// parent
					std::weak_ptr<nc_sc_a::base>						parent_;
					
					/// physics
					jess::shared_ptr<ncap::base>						physics_;
					/// renderer
					jess::shared_ptr<ncar::base>						renderer_;
					

					
					
					/// materials
					jess::map<nebula::content::actor::admin::material>			materials_;
					
					/// flag
					int									flag_;
					
					/// pose
					bnu::matrix<FLOAT>							pose_;
				};
			}
		}
	}
}

#endif








