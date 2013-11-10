#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_STATIC_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_STATIC_HPP__

#include <nebula/content/actor/physics/rigid_actor.hpp>

namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace physics
			{
				/// rigid static
				class rigid_static:
					public n34200::rigid_actor
				{
					protected:
						/// copy ctor
						rigid_static( rigid_static const & ) = default;
						/// assignment
						rigid_static&						operator=( rigid_static const & ) = default;
						/// ctor
						rigid_static( std::shared_ptr<n34100::base> );

					public:
						/// dtor
						virtual ~rigid_static();
						/// Initialize
						virtual void						init();
						/// ShutDown
						virtual	void						shutdown();
						/// Update
						virtual	void						update();
						virtual void						refresh(){}
						/// Render
						virtual	void						render( std::shared_ptr<n23000::base> );
						/// Step
						virtual	void						step( float );
				};
			}
		}
	}
}


#endif





