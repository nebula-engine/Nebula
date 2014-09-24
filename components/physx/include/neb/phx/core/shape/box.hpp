#ifndef PHYSX_SHAPE_BOX_HH
#define PHYSX_SHAPE_BOX_HH


#include <neb/phx/core/shape/base.hpp>

namespace neb { namespace phx { namespace core { namespace shape {


	class box:
		virtual public neb::phx::core::shape::base
	{
		public:
<<<<<<< HEAD
			box(std::shared_ptr<neb::phx::core::shape::util::parent> parent);

			virtual void				init() = 0;
=======
			box();

			virtual void				init(neb::core::core::shape::util::parent * const & p) = 0;
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
			virtual void				release() = 0;
			virtual void				step(gal::etc::timestep  const & ts) = 0;


			virtual physx::PxGeometry*		to_geo();
	};



}}}}

#endif
