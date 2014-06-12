#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_ACTOR_LOCAL_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_ACTOR_LOCAL_HPP__


#include <Nebula/Actor/Local.hh>
#include <Nebula/Actor/Actor/Base.hh>

namespace neb { namespace core { namespace actor {
namespace neb {
	namespace Actor {
		namespace Actor {
			class Local:
				virtual public neb::Actor::Actor::Base,
				virtual public neb::Actor::Local
			{
				public:
					virtual void		step(neb::core::TimeStep const & ts);
			};
		}
	}
}

#endif


