#ifndef NEB_PHX_CAMERA_PROJ_BASE_HPP
#define NEB_PHX_CAMERA_PROJ_BASE_HPP

#include <vector>
#include <memory>

#include <glm/glm.hpp>

#include <gal/etc/timestep.hpp>

#include <PxPhysicsAPI.h>

// neb/phx/camera/proj/base.hpp

namespace neb { namespace phx { namespace camera { namespace proj {
	/** @brief @Base */
	class base
	{
		public:
			/** @brief Constructor */
			base();
			
			//init(std::shared_ptr<neb::gfx::environ::base>)
			
			/** @brief step
			 * @todo explain when in timeline this occurs and in which thread and why
			 */
			//void						step(gal::etc::timestep const & ts);
		protected:
			/** @brief Parent */
			//std::weak_ptr<neb::gfx::environ::base>		parent_;
			// persistence
		public:
			physx::PxConvexMeshGeometry*			_M_px_geometry;
	};
}}}}

#endif
