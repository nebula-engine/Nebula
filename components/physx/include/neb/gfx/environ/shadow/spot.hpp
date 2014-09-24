#ifndef NEBULA_GFX_ENVIRON_SHADOW_SPOT_HPP
#define NEBULA_GFX_ENVIRON_SHADOW_SPOT_HPP

#include <neb/core/core/actor/util/decl.hpp>
#include <neb/core/util/typedef.hpp>

#include <neb/gfx/camera/util/decl.hpp>
#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/glsl/util/decl.hpp>
#include <neb/gfx/environ/base.hpp>
#include <neb/gfx/core/light/util/decl.hpp>

namespace neb { namespace gfx { namespace environ { namespace shadow {

	/** @brief base
	 *
	 * Abstract class that contains functions and data needed to render a specific kind of drawable.
	 */
	class spot: virtual public neb::gfx::environ::base {
		public:
			typedef std::shared_ptr<neb::gfx::glsl::program::shadow_directional>	program_shared;
			typedef std::shared_ptr<neb::gfx::camera::view::base>			view_shared;
			typedef std::shared_ptr<neb::gfx::camera::proj::base>		proj_shared;
			typedef neb::gfx::core::light::directional		light_type;
			typedef std::shared_ptr<light_type>			light_shared;
			typedef std::weak_ptr<light_type>			light_weak;
		public:
			spot();
			virtual void		init();
			virtual void		step(gal::etc::timestep const & ts);
			virtual void		render(
					std::shared_ptr<neb::gfx::context::base> context);
		public:
			/** @brief View Space Camera
			 * 
			 * @note OWNED
			 */			
			view_shared			view_;
			/** @brief Clip Space Camera
			 * 
			 * @note OWNED
			 */
			proj_shared			proj_;


			light_weak			light_;
	};


}}}


#endif
