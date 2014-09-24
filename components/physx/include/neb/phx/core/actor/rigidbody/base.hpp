#ifndef __PX_CONTENT_ACTOR_RIGIDBODY_BASE_HPP
#define __PX_CONTENT_ACTOR_RIGIDBODY_BASE_HPP

#include <PxPhysicsAPI.h>

#include <neb/core/pose.hpp>

#include <neb/phx/core/actor/rigidactor/base.hpp>
#include <neb/phx/core/actor/util/decl.hpp>

namespace neb { namespace phx { namespace core { namespace actor { namespace rigidbody {


	/** @brief base */
	class base:
		virtual public phx::core::actor::rigidactor::base
	{

		public:
			base(std::shared_ptr<phx::core::actor::util::parent>);

			virtual void					init() = 0;
			virtual void					release() = 0;
			virtual void					step(gal::etc::timestep const & ts);

			/** @brief create physics
			 *
			 * @note implemented by rigidstatic and rigiddynamic
			 */
			virtual void					create_physics() = 0;
			/** @brief initialize physics
			 *
			 * @note implemented by rigidstatic and rigiddynamic
			 */
		virtual void					init_physics() = 0;

			virtual void					add_force(double);
			//virtual void					setPose(neb::core::pose const & pose) = 0;
			void						create_control(std::shared_ptr<neb::gfx::window::base> window);
		public:
			shared_ptr<neb::phx::core::actor::control::rigidbody::base>		control_;
			glm::vec3		force_;
			glm::vec3		torque_;
	};
}}}}}

#endif


