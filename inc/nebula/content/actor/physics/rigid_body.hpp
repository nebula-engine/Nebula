#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_BODY_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_BODY_HPP__

#include <boost/numeric/ublas/vector.hpp>

#include <nebula/content/actor/physics/rigid_actor.hpp>

namespace bnu = boost::numeric::ublas;

namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace physics
			{
				/// rigid dynamic
				class rigid_body:
					public nebula::content::actor::physics::rigid_actor
				{
				public:
					///@name ctor and dtor
					///@{
					// Ctor
					rigid_body();
					/// Copy Ctor
					rigid_body(const rigid_body&);
					/// Dtor
					~rigid_body();
					///@}

					///@name operator
					///@{
					/// assignment
					rigid_body&								operator=(const rigid_body&);
					///@}

				

					/// init
					virtual	void								init( jess::shared_ptr<nebula::content::actor::admin::base>&);
					/// shutdown
					virtual	void								shutdown();
					/// update
					virtual	void								update();
					/// step
					virtual	void								step(FLOAT);
					/// render
					virtual	void								render(const jess::shared_ptr<nebula::platform::renderer::base>&);
				
				
					FLOAT									density_;
					bnu::vector<FLOAT>							velocity_;
				
					
				};
			}
		}
	}
}

#endif








