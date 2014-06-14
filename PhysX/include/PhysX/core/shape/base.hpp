#ifndef PHYSX_SHAPE_H__
#define PHYSX_SHAPE_H__

#include <map>

#include <PxPhysicsAPI.h>

#include <Nebula/Shape/Base.hh>

namespace px { namespace core { namespace shape {


	class base: virtual public neb::Shape::Base {
		public:
			base(sp::shared_ptr<neb::Shape::Util::Parent>);

			virtual void		init();
			void			create_physics();
			physx::PxGeometry*	to_geo();
		public:
			physx::PxShape*		px_shape_;


	};

}}}

#endif




