#ifndef NEBULA_CORE_SCENE_UTIL_CAST_HH
#define NEBULA_CORE_SCENE_UTIL_CAST_HH

#include <Nebula/Util/Shared.hh>
#include <Nebula/Scene/Util/Types.hh>

namespace Neb {
        namespace Scene {
                namespace Util {
                        class Cast: virtual public Neb::Util::Shared {
                                public:
                                        Neb::Scene::Base_s              isSceneBase();
                        };
                }
        }
}

#endif
