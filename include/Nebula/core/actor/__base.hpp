#ifndef NEBULA_ACTOR___BASE_HPP
#define NEBULA_ACTOR___BASE_HPP

#include <boost/thread.hpp>

#include <Nebula/util/shared.hpp>

namespace neb {
	namespace actor {
		class __base: virtual public neb::std::shared {
			public:
				boost::mutex	mutex_;
		};
	}
}

#endif
