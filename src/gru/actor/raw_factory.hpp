#ifndef __GLUTPP_ACTOR_RAW_FACTORY_H__
#define __GLUTPP_ACTOR_RAW_FACTORY_H__

#include <gru/actor/Type.hpp>

namespace glutpp {
	namespace actor {
		/** @brief Data Factory.
		 * Used to ensure correct derived class is allocated.
		 * Because allocation is expensive, should make @c create private and track usage using friends. */
		class raw_factory {
			public:
				friend class...;
			protected:
				virtual boost::shared_ptr<glutpp::actor::raw>		create(glutpp::actor::Type);
		};
	}
}

#endif
