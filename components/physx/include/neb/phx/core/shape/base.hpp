#ifndef PHYSX_SHAPE_BASE_H__
#define PHYSX_SHAPE_BASE_H__

#include <map>

#include <PxPhysicsAPI.h>

#include <neb/core/core/shape/base.hpp>

#include <neb/phx/core/shape/util/parent.hpp>

namespace neb { namespace phx { namespace core { namespace shape {


	class base: virtual public neb::core::core::shape::base {
		public:
<<<<<<< HEAD
			base(std::shared_ptr<phx::core::shape::util::parent>);
			virtual ~base();

			virtual void		init();
=======
			base();
			virtual ~base();

			virtual void		init(neb::core::core::shape::util::parent * const & p);
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
			virtual void		release();
			virtual void		step(gal::etc::timestep const & ts);


<<<<<<< HEAD
			void				create_physics();
			virtual physx::PxGeometry*	to_geo();
		public:
			std::shared_ptr<phx::core::shape::util::parent>		getPxParent();
=======
			virtual void		create_physics();
			virtual physx::PxGeometry*	to_geo();
		public:
			//std::shared_ptr<phx::core::shape::util::parent>		getPxParent();
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507

			physx::PxShape*		px_shape_;


	};

}}}}

#endif




