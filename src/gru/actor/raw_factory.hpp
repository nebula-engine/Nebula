#ifndef __GLUTPP_ACTOR_RAW_FACTORY_H__
#define __GLUTPP_ACTOR_RAW_FACTORY_H__

#include <gru/actor/Type.hpp>

namespace glutpp {
	namespace actor {
		class raw_factory {
			public:	
				virtual boost::shared_ptr<glutpp::actor::raw>		create(glutpp::actor::Type);
		};
	}
}

#endif
