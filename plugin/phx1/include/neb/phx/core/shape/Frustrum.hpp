#ifndef PHYSX_CORE_SHAPE_FRUSTRUM_HH
#define PHYSX_CORE_SHAPE_FRUSTRUM_HH

#include <neb/phx/core/shape/base.hpp>

namespace neb { namespace phx { namespace core { namespace shape {
	class Frustrum:
		virtual public neb::phx::core::shape::base
	{
		public:
			virtual void				init(parent_t * const & parent);
			virtual void				release();
			virtual void				step(gal::etc::timestep  const & ts);
			virtual physx::PxGeometry*		to_geo();
	};
}}}}

#endif


