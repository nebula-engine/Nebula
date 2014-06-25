#ifndef NEBULA_SHAPE_BOX_HH
#define NEBULA_SHAPE_BOX_HH

#include <neb/core/shape/base.hpp>

namespace neb { namespace core { namespace shape {



		class box: virtual public neb::core::shape::base {
			public:
				box(sp::shared_ptr<neb::core::shape::util::parent> parent);

				virtual void			createMesh();
		};


}}}

#endif
