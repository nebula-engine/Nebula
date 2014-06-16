#ifndef NEBULA_CORE_SCENE_UTIL_CAST_HH
#define NEBULA_CORE_SCENE_UTIL_CAST_HH

#include <Galaxy-Standard/shared.hpp>

#include <Nebula/Scene/Util/Cast.hh>

namespace phx { namespace core { namespace scene { namespace util {


	class cast:
		virtual public neb::core::scene::util::cast
	{
		public:
			sp::shared_ptr<phx::core::scene::base>		isPxSceneBase();
	};


}}}}

#endif
