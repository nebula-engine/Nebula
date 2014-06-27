#ifndef NEB_FINAL_GFX_PHX_CORE_ACTOR_RIGIDDYNAMIC_BASE_HPP
#define NEB_FINAL_GFX_PHX_CORE_ACTOR_RIGIDDYNAMIC_BASE_HPP

#include <neb/phx/core/actor/rigiddynamic/base.hpp>

#include <neb/fin/gfx_phx/core/actor/rigidactor/base.hpp>


namespace neb { namespace fin { namespace gfx_phx { namespace core { namespace actor {

	namespace util {
		class parent;
	}

	namespace rigiddynamic {

		class base:
			virtual public phx::core::actor::rigiddynamic::base,
			virtual public neb::fin::gfx_phx::core::actor::rigidactor::base
		{
			public:
				base(::std::shared_ptr<neb::fin::gfx_phx::core::actor::util::parent> parent);

				virtual void						init();
				virtual void						release();
				virtual void						step(gal::std::timestep const & ts);


		};
	}


}}}}}


#endif



