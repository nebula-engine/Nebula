#ifndef NEB_PHX_UTIL_LOG_HPP
#define NEB_PHX_UTIL_LOG_HPP

#include <gal/log/log.hpp>

namespace neb {
	namespace phx {
		extern severity_level		sl;
		namespace core {
			namespace scene {
				extern severity_level		sl;
			}
			namespace actor {
				extern severity_level		sl;
			}
			namespace shape {
				extern severity_level		sl;
			}
		}
	}
}

#endif
