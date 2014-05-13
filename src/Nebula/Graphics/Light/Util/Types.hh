#ifndef NEBULA_GRAPHICS_LIGHT_UTIL_TYPES_HH
#define NEBULA_GRAPHICS_LIGHT_UTIL_TYPES_HH

namespace Neb {
	/** @brief %Light */
	namespace Light {
		/** @brief %Util */
		namespace Util {
			class Parent;

			typedef std::shared_ptr<Parent>		Parent_s;
			typedef std::weak_ptr<Parent>		Parent_w;
		}

		class Base;

		typedef std::shared_ptr<Base>		Base_s;
		typedef std::weak_ptr<Base>		Base_w;

	}
}

#endif

