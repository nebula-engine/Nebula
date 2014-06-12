#ifndef NEBULA_UTIL_DISPATCH_HH
#define NEBULA_UTIL_DISPATCH_HH

namespace neb {
        namespace Util {
                struct dispatch_init {
                        template<class E> inline static void    visit(E* const & e) {
                                e->E::init();
                        }
                };
                struct dispatch_step {
                        template<class E> inline static void    visit(
                                        E* const & e,
                                        double const & time,
                                        double const & dt) {
                                e->E::step(time, dt);
                        }
                };
        }
}

#endif
