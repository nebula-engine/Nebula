#ifndef NEBULA_GFX_SHAPE_BOX_HH
#define NEBULA_GFX_SHAPE_BOX_HH

#include <neb/gfx/core/shape/base.hpp>

namespace neb {
	namespace gfx {
		namespace core {
			namespace shape {
				class box:
					virtual public neb::gfx::core::shape::base
				{
					public:
						box();

						virtual void			createMesh();
				};
			}
		}
	}
}

#endif
