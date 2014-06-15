#ifndef PHYSX_SHAPE_BASE_H__
#define PHYSX_SHAPE_BASE_H__

#include <map>

#include <PxPhysicsAPI.h>

#include <Nebula/Shape/Base.hh>

#include <PhysX/core/shape/util/parent.hpp>

namespace phx { namespace core { namespace shape {


	class base: virtual public neb::core::shape::base {
		public:
			base(sp::shared_ptr<neb::core::shape::util::parent>);
			virtual ~base();

			virtual void		init();
			virtual void		release();
			virtual void		step(neb::core::TimeStep const & ts);


			void			create_physics();
			physx::PxGeometry*	to_geo();
		public:
			sp::shared_ptr<phx::core::shape::util::parent>		parent_;

			physx::PxShape*		px_shape_;


	};

}}}

#endif




