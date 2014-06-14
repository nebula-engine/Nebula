#ifndef NEBULA_SHAPE_BOX_HH
#define NEBULA_SHAPE_BOX_HH

#include <Nebula/Shape/Base.hh>

namespace neb { namespace core { namespace shape {



		class Box: virtual public neb::core::shape::base {
			public:
				Box(sp::shared_ptr<neb::core::shape::util::parent> parent);

				virtual void			createMesh();
		};


}}}

#endif
