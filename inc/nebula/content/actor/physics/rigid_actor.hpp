#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_ACTOR_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_ACTOR_HPP__

#include <nebula/content/actor/physics/actor.hpp>

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
				class rigid_actor:
					virtual public nebula::content::actor::physics::actor
				{
					public:
						typedef std::shared_ptr<rigid_actor>			shared_t;
					protected:
						/** \brief copy ctor
						*/
						rigid_actor( rigid_actor const & ) = default;
						/** \brief assignment
						*/
						rigid_actor&						operator=( rigid_actor const & ) = default;
						/** \brief ctor
						*/
						rigid_actor( jess::shared_ptr<n34100::base> );
					public:
						/** \brief dtor
						*/
						~rigid_actor();
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
						/** \brief create shapes
						*/
						virtual	void						create_shapes();
				};
			}
		}
	}
}

#endif








