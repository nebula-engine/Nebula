#ifndef NEB_GFX_UTIL_LOG_HPP
#define NEB_GFX_UTIL_LOG_HPP

#include <gal/log/log.hpp>

namespace neb {
	namespace gfx {
		extern severity_level		sl;
		namespace core {
			namespace actor {
				extern severity_level		sl;
			}
			namespace shape {
				extern severity_level		sl;
			}
			namespace light {
				extern severity_level		sl;
			}
		}
	}
}

#endif
