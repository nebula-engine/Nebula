#ifndef NEB_FINAL_GFX_PHX_CORE_ACTOR_RIGIDACTOR_BASE_HPP
#define NEB_FINAL_GFX_PHX_CORE_ACTOR_RIGIDACTOR_BASE_HPP

#include <PhysX/core/actor/rigidactor/base.hpp>

namespace neb { namespace fin { namespace gfx_phx { namespace core { namespace actor { namespace rigidactor {

	class base:
		virtual public phx::core::actor::rigidactor::base,
		virtual public neb::fin::gfx_phx::core::actor::base
	{
		public:
			::std::weak_ptr<neb::core::shape::base>				createShapeBoxUninitialized(glm::vec3 size);
			::std::weak_ptr<neb::core::shape::base>				createShapeBox(glm::vec3 size);
	};
}


#endif



