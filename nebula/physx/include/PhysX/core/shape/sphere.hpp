#ifndef PHYSX_CORE_SHAPE_SPHERE_HH
#define PHYSX_CORE_SHAPE_SPHERE_HH

#include <PhysX/core/shape/base.hpp>

namespace phx { namespace core { namespace shape {


	class sphere:
		virtual public phx::core::shape::base
	{
			public:
				virtual void				init();
				virtual void				release();
				virtual void				step(gal::std::timestep  const & ts);


				virtual physx::PxGeometry*		to_geo();
		};


}}}

#endif
