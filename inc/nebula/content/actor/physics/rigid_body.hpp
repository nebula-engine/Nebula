#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_BODY_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_BODY_HPP__

#include <nebula/content/actor/physics/rigid_actor.hpp>

namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace physics
			{
				/** \brief rigid dynamic
				*/
				class rigid_body:
					public nebula::content::actor::physics::rigid_actor
				{
					protected:
						/** \brief copy ctor
						*/
						rigid_body( rigid_body const & ) = default;
						/** \brief assignment
						*/
						rigid_body&						operator=( rigid_body const & ) = default;
						/** \brief ctor
						*/
						rigid_body( n34100::base::shared_t );
					public:
						/** \brief dtor
						*/
						~rigid_body();
						/** \brief init
						*/
						virtual	void						init();
						/** \brief shutdown
						*/
						virtual	void						shutdown();
						/** \brief update
						*/
						virtual	void						update();
						/** \brief step
						*/
						virtual	void						step( float );
						/** \brief render
						*/
						virtual	void						render( n23000::base::shared_t );
						/** \brief density
						*/
						float							density_;
						/** \brief velocity
						*/
						physx::PxVec3						velocity_;
				};
			}
		}
	}
}

#endif








