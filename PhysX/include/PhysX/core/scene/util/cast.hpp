#ifndef PHYSX_CORE_SCENE_UTIL_CAST_HH
#define PHYSX_CORE_SCENE_UTIL_CAST_HH

#include <Galaxy-Standard/shared.hpp>

#include <Nebula/core/scene/Util/Cast.hh>

#include <PhysX/core/scene/util/decl.hpp>

namespace phx { namespace core { namespace scene { namespace util {


	class cast:
		virtual public neb::core::scene::util::cast
	{
		public:
			sp::shared_ptr<phx::core::scene::base>			isPxSceneBase();
			sp::shared_ptr<phx::core::scene::local>			isPxSceneLocal();
			sp::shared_ptr<phx::core::scene::remote>		isPxSceneRemote();
	};


}}}}

#endif
