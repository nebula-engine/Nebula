#ifndef __GLUTPP_SHAPE_EMPTY_H__
#define __GLUTPP_SHAPE_EMPTY_H__

#include <Nebula/Shape/Base.hh>

namespace neb { namespace core {
	namespace shape {
		class empty: public neb::core::shape::base {
			public:
				empty(sp::shared_ptr<neb::core::shape::util::parent> parent): neb::core::shape::base(parent) {}
				virtual void			createMesh() {}
				
				virtual void					draw_elements(
						sp::shared_ptr<neb::gfx::context::base> context,
						sp::shared_ptr<neb::glsl::program> p,
						neb::core::pose const & pose) {}
		};
	}
}}

#endif




