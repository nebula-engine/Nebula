#ifndef NEBULA_GFX_ENVIRON_SHADOW_DIRECTIONAL_HPP
#define NEBULA_GFX_ENVIRON_SHADOW_DIRECTIONAL_HPP

#include <neb/core/core/actor/util/decl.hpp>
#include <neb/core/util/typedef.hpp>

#include <neb/gfx/camera/util/decl.hpp>
#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/glsl/util/decl.hpp>
#include <neb/gfx/environ/base.hpp>
#include <neb/gfx/environ/shadow/base.hpp>
#include <neb/gfx/core/light/util/decl.hpp>

namespace neb { namespace gfx { namespace environ {

	/** @brief base
	 *
	 * Abstract class that contains functions and data needed to render a specific kind of drawable.
	 */
	class shadow_directional:
		virtual public neb::gfx::environ::single<neb::gfx::camera::view::shadow::directional>,
		virtual public neb::gfx::environ::shadow::base<neb::gfx::core::light::directional>
       	{
		public:
			typedef std::shared_ptr<neb::gfx::glsl::program::base>	program_shared;
			typedef std::shared_ptr<neb::gfx::camera::view::base>			view_shared;
			typedef std::shared_ptr<neb::gfx::camera::proj::base>		proj_shared;
			typedef neb::gfx::core::light::directional		light_type;
			typedef std::shared_ptr<light_type>			light_shared;
			typedef std::weak_ptr<light_type>			light_weak;
		public:
			shadow_directional();
			virtual void		init();
			virtual void		step(gal::etc::timestep const & ts);

			virtual void		render(
					std::shared_ptr<neb::gfx::context::base> context);

			virtual bool		shouldRender();
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


	};


}}}


#endif
