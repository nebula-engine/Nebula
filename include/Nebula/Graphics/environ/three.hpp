#ifndef NEBULA_GFX_ENVIRON_THREE_HPP
#define NEBULA_GFX_ENVIRON_THREE_HPP

#include <Nebula/Util/typedef.hpp>
#include <Nebula/Graphics/Types.hh>
#include <Nebula/Graphics/environ/base.hpp>


namespace neb { namespace gfx { namespace environ {

	/** @brief base
	 *
	 * Abstract class that contains functions and data needed to render a specific kind of drawable.
	 */
	class three: virtual public neb::gfx::environ::base {
		public:
			virtual void		init();
			virtual void		step(neb::core::TimeStep const & ts);

			virtual void		render(sp::shared_ptr<neb::gfx::context::base> context);
		public:
					/** @brief View Space Camera
			 * 
			 * @note OWNED
			 */			
			sp::shared_ptr<neb::gfx::Camera::View::base>			view_;
			/** @brief Clip Space Camera
			 * 
			 * @note OWNED
			 */
			sp::shared_ptr<neb::gfx::Camera::Projection::base>		proj_;
			/** @brief %Drawable
			 * 
			 * @note WEAK
			 * 
			 * content to draw
			 */
			//sp::weak_ptr<neb::gfx::drawable::three>				drawable_;
	};


}}}


#endif
