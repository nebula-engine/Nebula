#ifndef PX_CONTENT_ACTOR_RIGIDACTOR_BASE_HPP
#define PX_CONTENT_ACTOR_RIGIDACTOR_BASE_HPP

#include <PxPhysicsAPI.h>

#include <neb/fnd/core/actor/rigidactor/Base.hpp>

#include <neb/phx/core/actor/actor/base.hpp>
#include <neb/phx/core/actor/util/decl.hpp>

namespace neb { namespace phx { namespace core { namespace actor { namespace rigidactor {
	class base:
		virtual public neb::fnd::core::actor::rigidactor::base,
		virtual public neb::phx::core::actor::actor::base
	{
		public:
			//base(::std::shared_ptr<neb::phx::core::actor::util::parent>);
			
			virtual void						init(neb::fnd::core::actor::util::parent * const &) = 0;
			virtual void						release() = 0;
			virtual void						step(gal::etc::timestep const & ts) = 0;
			void							setupFiltering();
			virtual void						create_physics() = 0;
			virtual void						init_physics() = 0;
			//virtual void						add_force(real) = 0;
			//virtual void						set_pose(physx::PxTransform);
			virtual void						set_pose_global(gal::math::pose pose);
			/** @name convenience functions
			 * @{
			 *
			 * @ note typeof returned actor will be phx::core::shape::box
			 */
			//virtual std::weak_ptr<neb::fnd::shape::base>		createShapeBoxUninitialized();
			/** @} */
	};
}}}}}

#endif


