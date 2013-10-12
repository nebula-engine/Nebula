#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_BASE_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_BASE_HPP__

#include <jess/shared_ptr.hpp>
#include <jess/map.hpp>

#include <nebula/ns.hpp>

namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace physics
			{
				/// base
				class base
				{
					protected:
						/// copy ctor
						base( base const & );
						/// assignment
						base&									operator=( base const & );
					public:
						/// ctor
						base( jess::shared_ptr<n34100::base> );
						/// dtor
						~base();
						/// init
						virtual	void								init();
						/// shutdown
						virtual	void								shutdown();
						/// update
						virtual	void								update();
						/// step
						virtual	void								step( float );
						/// render
						virtual void								render( jess::shared_ptr<n23000::base> rnd );
						/// create shapes
						virtual	void								create_shapes();
						/// parent
						std::weak_ptr<n34100::base>						parent_;
						/// materials
						jess::map<n34200::material>						materials_;
				};
			}
		}
	}
}


#endif








