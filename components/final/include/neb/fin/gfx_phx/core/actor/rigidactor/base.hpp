#ifndef NEB_FINAL_GFX_PHX_CORE_ACTOR_RIGIDACTOR_BASE_HPP
#define NEB_FINAL_GFX_PHX_CORE_ACTOR_RIGIDACTOR_BASE_HPP

#include <neb/phx/core/actor/rigidactor/base.hpp>

#include <neb/fin/gfx_phx/core/actor/base.hpp>

namespace neb { namespace fin { namespace gfx_phx { namespace core { namespace actor { namespace rigidactor {

	class base:
		virtual public phx::core::actor::rigidactor::base,
		virtual public neb::fin::gfx_phx::core::actor::base
	{
		public:
			//base(std::shared_ptr<> parent);
			virtual void							init(neb::core::core::actor::util::parent * const & p) = 0;
			virtual void							release() = 0;
			virtual void							step(gal::etc::timestep const & ts) = 0;


			weak_ptr<neb::core::core::shape::base>				createShapeBoxUninitialized(glm::vec3 size);
			weak_ptr<neb::core::core::shape::base>				createShapeBox(neb::core::pose, glm::vec3 size);
	};

}}}}}}


#endif



