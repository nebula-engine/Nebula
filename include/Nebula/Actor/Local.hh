#ifndef NEBULA_ACTOR_LOCAL_HH
#define NEBULA_ACTOR_LOCAL_HH


#include <Nebula/Actor/Base.hh>
#include <Nebula/Core/TimeStep.hpp>

namespace neb { namespace core { namespace actor {
namespace neb {
	namespace Actor {
		class Local: virtual public neb::Actor::Base {
			public:
				virtual void		step(neb::core::TimeStep const & ts);
		};
	}
}

#endif





