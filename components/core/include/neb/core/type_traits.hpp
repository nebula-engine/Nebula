#ifndef NEBULA_TYPE_TRAITS_HPP
#define NEBULA_TYPE_TRAITS_HPP

#include <neb/core/core/actor/util/decl.hpp>

namespace gal { namespace stl {
	template<typename T> class parent;
	template<typename T> class child;
}}

// decls

namespace neb {
	namespace gfx {
		namespace gui {
			namespace object {
				class base;
				namespace util {
					class parent;
				}
			}
		}
	}
}



// traits

namespace neb {

	template<typename T> struct type_traits {};

	template<> struct type_traits<neb::core::core::actor::__base>
	{
		typedef neb::core::core::actor::util::parent			parent_t;
		typedef gal::stl::child<parent_t>				child_t;
	};

	template<> struct type_traits<neb::gfx::gui::object::base>
	{
		typedef neb::gfx::gui::object::util::parent			parent_t;
		typedef gal::stl::child<parent_t>				child_t;
	};
	

}

#endif

