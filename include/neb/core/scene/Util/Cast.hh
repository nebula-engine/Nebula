#ifndef NEBULA_CORE_SCENE_UTIL_CAST_HH
#define NEBULA_CORE_SCENE_UTIL_CAST_HH

#include <neb/util/shared.hpp>

#include <neb/core/scene/Util/Types.hh>

namespace neb { namespace core {
        namespace scene {
                namespace util {
                        class cast: virtual public neb::std::shared {
                                public:
                                        sp::shared_ptr<neb::core::scene::base>			isSceneBase();
                                        sp::shared_ptr<neb::core::scene::local>			isSceneLocal();
                                        sp::shared_ptr<neb::core::scene::remote>		isSceneRemote();
                        };
                }
        }
}}

#endif
