#ifndef NEBULA_UTIL_RELEASE_HH
#define NEBULA_UTIL_RELEASE_HH

#include <boost/signals2.hpp>

namespace Neb {
        namespace Util {
                class Release {
                        public:
                                void                                    release();
                                virtual void                            releaseDerived() = 0;
                                
                                boost::signals2::signal<void()>         sig_release_;
                };
        }
}

#endif
