#ifndef PHYSX_CORE_ACTOR_PARENT_HPP
#define PHYSX_CORE_ACTOR_PARENT_HPP

#include <neb/core/core/actor/util/parent.hpp>

#include <neb/phx/core/scene/util/decl.hpp>

namespace neb { namespace phx { namespace core { namespace actor { namespace util {
	/** @brief @parent
	 * abstract class for parent of a %phx %actor
	 */
	class parent:
		virtual public neb::core::core::actor::util::parent
	{
		public:
			parent();
			virtual ~parent();

			virtual void						init();
		public:
			shared_ptr<neb::phx::core::scene::base>			getScene();
	};
}}}}}

#endif



