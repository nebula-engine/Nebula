#ifndef NEBULA_GRAPHICS_GUI_LAYOUT_TYPES_HH
#define NEBULA_GRAPHICS_GUI_LAYOUT_TYPES_HH

namespace Neb {
	namespace Graphics {
		namespace GUI {
			namespace Layout {
				namespace Util {
					class Parent;

					typedef std::shared_ptr<Parent>		Parent_s;
					typedef std::weak_ptr<Parent>		Parent_w;
					typedef std::unique_ptr<Parent>		Parent_u;
				}

				class Base;

				typedef std::shared_ptr<Base>		Base_s;
				typedef std::weak_ptr<Base>		Base_w;
				typedef std::unique_ptr<Base>		Base_u;
			}
		}
	}
}

#endif

