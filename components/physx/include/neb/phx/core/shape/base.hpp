#ifndef PHYSX_SHAPE_BASE_H__
#define PHYSX_SHAPE_BASE_H__

#include <map>

#include <PxPhysicsAPI.h>

#include <neb/core/core/shape/base.hpp>

#include <neb/phx/core/shape/util/parent.hpp>

namespace neb { namespace phx { namespace core { namespace shape {


	class base: virtual public neb::core::core::shape::base {
		public:
			base(std::shared_ptr<phx::core::shape::util::parent>);
			virtual ~base();

			virtual void		init();
			virtual void		release();
			virtual void		step(gal::etc::timestep const & ts);


			void				create_physics();
			virtual physx::PxGeometry*	to_geo();
		public:
			std::shared_ptr<phx::core::shape::util::parent>		getPxParent();

			physx::PxShape*		px_shape_;


	};

}}}}

#endif




