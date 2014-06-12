#ifndef NEBULA_CORE_SCENE_UTIL_CAST_HH
#define NEBULA_CORE_SCENE_UTIL_CAST_HH

#include <Nebula/Util/shared.hpp>

#include <Nebula/Scene/Util/Types.hh>

namespace neb {
        namespace Scene {
                namespace Util {
                        class Cast: virtual public neb::std::shared {
                                public:
                                        Neb::Scene::Base_s              isSceneBase();
                        };
                }
        }
}

#endif
