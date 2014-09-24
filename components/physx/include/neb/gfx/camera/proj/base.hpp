#ifndef GLUTPP_CAMERA_PROJECTION_BASE_HPP
#define GLUTPP_CAMERA_PROJECTION_BASE_HPP

#include <vector>
#include <memory>

#include <glm/glm.hpp>

#include <gal/etc/timestep.hpp>

#include <PxPhysicsAPI.h>

#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/glsl/util/decl.hpp>

namespace neb {namespace gfx {namespace camera {namespace proj {
	/** @brief @Base */
	class base {
		public:
			/** @brief Constructor */
			base(std::shared_ptr<neb::gfx::environ::base>);

			virtual glm::mat4&				proj() = 0;
			virtual void					calculate() = 0;
			void						calculate_geometry();
			
			void						load(neb::gfx::glsl::program::base const * const p);
			/** @brief step
			 * @todo explain when in timeline this occurs and in which thread and why
			 */
			void						step(gal::etc::timestep const & ts);
		protected:
			/** @brief Parent */
			std::weak_ptr<neb::gfx::environ::base>		parent_;
			// persistence
			glm::mat4					_M_matrix;
		public:
			physx::PxConvexMeshGeometry*			_M_px_geometry;
	};
}}}}


#endif


