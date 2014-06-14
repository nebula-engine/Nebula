#ifndef NEBULA_CORE_SCENE_UTIL_CAST_HH
#define NEBULA_CORE_SCENE_UTIL_CAST_HH

#include <Galaxy-Standard/shared.hpp>

#include <Nebula/Scene/Util/Types.hh>

namespace Neb {
        namespace Scene {
                namespace util {
                        class Cast: virtual public gal::std::shared {
                                public:
                                        sp::shared_ptr<neb::Scene::base>              isSceneBase();
                        };
                }
        }
}

#endif
