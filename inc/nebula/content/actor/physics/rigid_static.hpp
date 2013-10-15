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
						rigid_static( rigid_static const & _actor_ ): actor( _actor_ ), rigid_actor( _actor_ )
						{

						}
						/// assignment
						rigid_static&	operator=( rigid_static const & )
						{
							return *this;
						}
					public:
						/// ctor
						rigid_static( jess::shared_ptr<n34100::base> );
						/// dtor
						virtual ~rigid_static();
						/// Initialize
						virtual void						init();
						/// ShutDown
						virtual	void						shutdown();
						/// Update
						virtual	void						update();
						/// Render
						virtual	void						render( jess::shared_ptr<n23000::base> );
						/// Step
						virtual	void						step( float );




						/// Create Shapes
						virtual	void						create_shape();


				};
			}
		}
	}
}


#endif





