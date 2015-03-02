#ifndef PHYSX_SHAPE_BASE_H__
#define PHYSX_SHAPE_BASE_H__

#include <map>

#include <PxPhysicsAPI.h>

#include <gal/stl/verbosity.hpp>

#include <neb/fnd/plug/phx/core/shape/Base.hpp>

//#include <neb/phx/core/shape/util/parent.hpp>
#include <neb/phx/tmp/Child.hpp>

namespace neb { namespace phx { namespace core { namespace shape {
	class base:
		//virtual public neb::fnd::core::shape::base,
		public gal::tmp::Verbosity<neb::phx::core::shape::base>,
		virtual public neb::fnd::plug::phx::core::shape::Base
		//virtual public neb::phx::tmp::Child<neb::fnd::core::shape::util::parent>
	{
		public:
			using gal::tmp::Verbosity<neb::phx::core::shape::base>::printv;
			base();
			virtual ~base();
			virtual void		init(parent_t * const & p);
			virtual void		release();
			virtual void		step(gal::etc::timestep const & ts);
			virtual void		create_physics();
			virtual physx::PxGeometry*	to_geo();
		public:
			//std::shared_ptr<phx::core::shape::util::parent>		getPxParent();

			physx::PxShape*		px_shape_;


	};

}}}}

#endif




