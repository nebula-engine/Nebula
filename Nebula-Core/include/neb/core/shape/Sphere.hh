#ifndef NEBULA_SHAPE_SPHERE_HH
#define NEBULA_SHAPE_SPHERE_HH

#include <neb/core/shape/Base.hh>

namespace neb { namespace core { namespace shape {


		class Sphere: virtual public neb::core::shape::base {
			public:
				virtual void			createMesh();
		};



}}}

#endif


