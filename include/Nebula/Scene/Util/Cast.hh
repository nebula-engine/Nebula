#ifndef NEBULA_CORE_SCENE_UTIL_CAST_HH
#define NEBULA_CORE_SCENE_UTIL_CAST_HH

#include <Nebula/Util/shared.hpp>

#include <Nebula/Scene/Util/Types.hh>

namespace neb {
        namespace scene {
                namespace util {
                        class cast: virtual public neb::std::shared {
                                public:
                                        sp::shared_ptr<neb::scene::base>              isSceneBase();
                        };
                }
        }
}

#endif
