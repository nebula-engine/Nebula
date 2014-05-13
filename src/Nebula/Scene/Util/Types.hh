#ifndef NEBULA_SCENE_TYPES_HH
#define NEBULA_SCENE_TYPES_HH

#include <memory>

namespace Neb {
	/** @brief %Scene */
	namespace Scene {
		/** @name %Utilities @{ */
		namespace Util {
			class Parent;


			typedef std::weak_ptr<Parent>		Parent_w;


			class Raw;
			class Address;

			typedef std::shared_ptr<Raw>		Raw_s;
			typedef std::weak_ptr<Raw>		Raw_w;

			typedef std::weak_ptr<Address>		Address_w;



		}

		enum flag {
			SHOULD_RELEASE = 1 << 0
		};

		class Base;


		typedef std::shared_ptr<Base>		Base_s;
		typedef std::unique_ptr<Base>		Base_u;
		typedef std::weak_ptr<Base>		Base_w;
	}
}

#endif

