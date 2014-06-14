#ifndef PHYSX_CORE_SHAPE_SPHERE_HH
#define PHYSX_CORE_SHAPE_SPHERE_HH

#include <Nebula/Shape/Sphere.hh>

#include <PhysX/core/shape/Base.hh>

namespace px { namespace core { namespace shape {


	class sphere:
		virtual public neb::Shape::Sphere,
		virtual public px::core::shape::base
	{
			public:
				virtual void				init();
				virtual void				release();
				virtual void				step(neb::core::TimeStep  const & ts);


				virtual physx::PxGeometry*		to_geo();
		};


}}}

#endif
