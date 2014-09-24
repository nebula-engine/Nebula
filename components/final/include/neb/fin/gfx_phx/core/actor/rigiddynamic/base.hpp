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
	
				base();
				~base();
				virtual void						init(neb::core::core::actor::util::parent * const &);
				virtual void						release();
				virtual void						step(gal::etc::timestep const & ts);


		};
	}


}}}}}


#endif



