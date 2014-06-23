#ifndef PHYSX_SHAPE_BOX_HH
#define PHYSX_SHAPE_BOX_HH

#include <Nebula/core/shape/Box.hh>

#include <PhysX/core/shape/base.hpp>

namespace phx { namespace core { namespace shape {


	class box:
		virtual public neb::core::shape::box,
		virtual public phx::core::shape::base
	{
		public:
			box(sp::shared_ptr<phx::core::actor::rigidactor::base> parent);

			virtual void				init();
			virtual void				release();
			virtual void				step(gal::std::timestep  const & ts);


			virtual physx::PxGeometry*		to_geo();
	};



}}}

#endif
