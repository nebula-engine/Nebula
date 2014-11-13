#ifndef NEBULA_GFX_ENVIRON_SHADOW_BASE_HPP
#define NEBULA_GFX_ENVIRON_SHADOW_BASE_HPP

#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/glsl/util/decl.hpp>
#include <neb/gfx/environ/three.hpp>


namespace neb { namespace gfx { namespace environ { namespace shadow {

	/** @brief base
	 *
	 * Abstract class that contains functions and data needed to render a specific kind of drawable.
	 */
	template<typename LIGHT> class base:
		virtual public neb::gfx::environ::three
	{
		public:
			typedef std::shared_ptr<neb::gfx::glsl::program::base>		program_shared;
			typedef std::weak_ptr<neb::gfx::environ::SceneDefault>		environ_scene_weak;
		public:
			virtual ~base() {}


			virtual void		init() = 0;
			virtual void		step(gal::etc::timestep const & ts) = 0;
			//virtual void		resize(int w, int h) = 0;
			virtual void		render(std::shared_ptr<neb::gfx::context::base> context) = 0;
			virtual bool		shouldRender() = 0;
			virtual bool		shouldRender(unsigned int) { return true; }
		public:	

			/** environ that uses the shadow map
			 * frustrum used to determine which shadowmaps need to be rendered
			 */
			environ_scene_weak			environ_scene_;

			std::weak_ptr<LIGHT>			light_;


	};


}}}}


#endif
