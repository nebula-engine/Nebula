#ifndef NEBULA_SHAPE_UTIL_TYPES_HH
#define NEBULA_SHAPE_UTIL_TYPES_HH

namespace Neb {
	/** @brief %Shape */	
	namespace shape {
		struct flag {
			enum e {
				SHOULD_RELEASE = 1 << 0,
				IMAGE          = 1 << 1,
			};
		};

		namespace util {
			class parent;

			typedef std::shared_ptr<Parent>		Parent_s;
			typedef std::unique_ptr<Parent>		Parent_u;
			typedef std::weak_ptr<Parent>		Parent_w;
		}

		class base;

		typedef std::shared_ptr<Base>		Base_s;
		typedef std::weak_ptr<Base>		Base_w;

	}
}
#endif
