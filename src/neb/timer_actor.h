#ifndef __NEBULA_TIMER_ACTOR__
#define __NEBULA_TIMER_ACTOR__

namespace neb {
        namespace timer {
                class actor: public gal::timer::timer {
                        public:
                                enum type {
                                        NONE = 0,
                                        RELEASE,
                                };
                        
                                actor(neb::actor::Base_s, neb::timer::actor::type, double);
                                
                                void  activate();
                                
                                neb::timer::actor::type         type_;
                                neb::actor::Base_w              actor_;
                };
        }
}

#endif
