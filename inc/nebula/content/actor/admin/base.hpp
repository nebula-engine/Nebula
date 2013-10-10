#ifndef __NEBULA_CONTENT_ACTOR_ADMIN_BASE_HPP__
#define __NEBULA_CONTENT_ACTOR_ADMIN_BASE_HPP__

#include <boost/numeric/ublas/matrix.hpp>

#include <jess/shared_ptr.hpp>
#include <jess/map.hpp>

#include <nebula/ns.hpp>

namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace admin
			{
				/// base
				class base:
					public jess::enable_shared_from_this<ncaa::base>
				{
				public:
					///@name ctor and dtor
					///@{
					// Ctor
					base();
					/// Copy Ctor
					base(const base&);
					/// Dtor
					virtual ~base();
					///@}
	
					///@name operator
					///@{
					/// assignment
					base&									operator=(const base&);
					///@}
	
					
	
					/// init
					virtual	void								init( jess::shared_ptr<nebula::content::scene::admin::base> );
					/// shutdown
					virtual	void								shutdown();
					/// update
					virtual	void								update();
					/// step
					virtual	void								step( FLOAT );
					/// render
					virtual	void								render( jess::shared_ptr<nebula::platform::renderer::base> );
					
					
					
					
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
					/// velocity
					bnu::vector<float>							velocity_;
				};
			}
		}
	}
}

#endif








