#ifndef __NEBULA_ACTOR_RAW_FACTORY_H__
#define __NEBULA_ACTOR_RAW_FACTORY_H__

#include <glutpp/actor/raw_factory.h>
#include <glutpp/config.h>

namespace neb {
        namespace actor {
                class raw_factory: public glutpp::actor::raw_factory {
                        public: 
                                virtual glutpp::actor::raw_s            create(int);
                };
        }
}

#endif



