#ifndef PHYSX_SHAPE_BOX_HH
#define PHYSX_SHAPE_BOX_HH

#include <neb/phx/core/shape/base.hpp>

namespace neb { namespace phx { namespace core { namespace shape {

	class box:
		virtual public neb::phx::core::shape::base
	{
		public:
			box();
			virtual void				init(parent_t * const & p);
			virtual void				release();
			virtual void				step(gal::etc::timestep  const & ts);
			virtual physx::PxGeometry*		to_geo();
	};



}}}}

#endif
