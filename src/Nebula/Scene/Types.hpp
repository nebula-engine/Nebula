#ifndef NEBULA_SCENE_TYPES_HH
#define NEBULA_SCENE_TYPES_HH

#include <memory>

#include <Nebula/Memory/smart_ptr.hpp>

namespace Neb {
	/** @brief %Scene */
	namespace Scene {
		/** @name %Utilities @{ */
		namespace Util {
			class Parent;

			
			typedef std::weak_ptr<Parent>		Parent_w;
		}

		enum flag {
			SHOULD_RELEASE = 1 << 0
		};

		class raw;
		class addr;
		class desc;

		class scene;

		typedef std::shared_ptr<raw>		raw_s;
		typedef Neb::weak_ptr<raw>		raw_w;

		typedef Neb::weak_ptr<addr>		addr_w;
		typedef Neb::weak_ptr<desc>		desc_w;

		typedef std::shared_ptr<scene>		scene_s;
		typedef Neb::unique_ptr<scene>		scene_u;
		typedef Neb::weak_ptr<scene>		scene_w;
	}
}

#endif

