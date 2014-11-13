#ifndef PHYSX_SHAPE_FRUSTRUM_HH
#define PHYSX_SHAPE_FRUSTRUM_HH


#include <neb/phx/core/shape/base.hpp>

#include <neb/gfx/camera/util/decl.hpp>

namespace neb { namespace phx { namespace core { namespace shape {


	class frustrum:
		virtual public neb::phx::core::shape::base
	{
		public:
			frustrum();

			//virtual void				init() = 0;
			//virtual void				release() = 0;
			//virtual void				step(gal::etc::timestep  const & ts) = 0;
			
			std::weak_ptr<neb::gfx::camera::proj::base>	camera_;
			
			virtual physx::PxGeometry*			to_geo();
	};



}}}}

#endif
