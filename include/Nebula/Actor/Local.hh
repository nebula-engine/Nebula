#ifndef NEBULA_ACTOR_LOCAL_HH
#define NEBULA_ACTOR_LOCAL_HH


#include <Nebula/Actor/Base.hh>
#include <Nebula/Core/TimeStep.hpp>

namespace neb { namespace core { namespace actor {
namespace neb {
	namespace Actor {
		class Local: virtual public Neb::Actor::Base {
			public:
				virtual void		step(Neb::Core::TimeStep const & ts);
		};
	}
}

#endif





