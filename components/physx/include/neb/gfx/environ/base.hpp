#ifndef NEBULA_GFX_ENVIRON_BASE_HPP
#define NEBULA_GFX_ENVIRON_BASE_HPP

#include <gal/etc/timestep.hpp>
#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/camera/util/decl.hpp>
#include <neb/gfx/glsl/util/decl.hpp>
#include <neb/gfx/environ/util/cast.hpp>
#include <neb/gfx/environ/util/flag.hpp>
#include <neb/gfx/Viewport.hpp>


namespace neb { namespace gfx { namespace environ {

	/** @brief base
	 *
	 * Abstract class that contains functions and data needed to render a specific kind of drawable.
	 */
	class base:
		virtual public neb::gfx::environ::util::cast
	{
		public:
			typedef std::shared_ptr<neb::gfx::glsl::program::base>		program_shared;
			typedef std::shared_ptr<neb::gfx::camera::view::base>		view_shared;
			typedef std::shared_ptr<neb::gfx::camera::proj::base>		proj_shared;
			//typedef neb::gfx::core::light::directional			light_type;
			//typedef std::shared_ptr<light_type>				light_shared;
			//typedef std::weak_ptr<light_type>				light_weak;
		public:
			virtual ~base() {}

			virtual void		init();
			virtual void		step(gal::etc::timestep const & ts);
			virtual void		resize(int w, int h);
			virtual void		render(std::shared_ptr<neb::gfx::context::base> context) = 0;
			virtual bool		shouldRender();
			virtual bool		shouldRender(unsigned int) { return true; }
		public:	
			/** @brief %Viewport
			 * 
			 * sub-rectangle within target
			 */
			neb::gfx::Viewport					viewport_;

			std::weak_ptr<neb::gfx::drawable::base>			drawable_;

			neb::gfx::environ::util::flag				flag_;

			proj_shared						proj_;
	};
	template<typename VIEW> class single:
		virtual public neb::gfx::environ::base
	{
		public:
			std::shared_ptr<VIEW>		view_;
	};
	template<typename VIEW> class multiple:
		virtual public neb::gfx::environ::base
	{
		public:
			std::shared_ptr<VIEW>		view_[6];
	};
}}}


#endif
