#ifndef NEBULA_CORE_CORE_ACTOR_UTIL_CAST_HH
#define NEBULA_CORE_CORE_ACTOR_UTIL_CAST_HH

#include <gal/itf/shared.hpp>

#include <neb/core/core/actor/util/decl.hpp>

using namespace std;

namespace neb { namespace core { namespace core { namespace actor { namespace util {
	class cast: virtual public gal::itf::shared {
		public:
			shared_ptr<neb::core::core::actor::base>			isActorBase();
	};
}}}}}

#endif

