#ifndef PHYSX_SHAPE_BOX_HH
#define PHYSX_SHAPE_BOX_HH

#include <Nebula/Shape/Box.hh>

#include <PhysX/core/shape/base.hpp>

namespace phx { namespace core { namespace shape {


	class box:
		virtual public neb::core::shape::Box,
		virtual public phx::core::shape::base
	{
		public:
			virtual void				init();
			virtual void				release();
			virtual void				step(neb::core::TimeStep  const & ts);


			virtual physx::PxGeometry*		to_geo();
	};



}}}

#endif
