#ifndef __GLUTPP_ACTOR_RAW_FACTORY_H__
#define __GLUTPP_ACTOR_RAW_FACTORY_H__

namespace glutpp {
	namespace actor {
		class raw_factory {
			public:	
				virtual glutpp::actor::raw_s		create(int);
		};
	}
}

#endif
