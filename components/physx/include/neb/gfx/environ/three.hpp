#ifndef NEBULA_GFX_ENVIRON_THREE_HPP
#define NEBULA_GFX_ENVIRON_THREE_HPP

#include <neb/core/core/actor/util/decl.hpp>
#include <neb/core/util/typedef.hpp>

#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/camera/util/decl.hpp>
#include <neb/gfx/glsl/util/decl.hpp>
#include <neb/gfx/environ/base.hpp>

namespace neb { namespace gfx { namespace environ {

	/** @brief base
	 *
	 * Abstract class that contains functions and data needed to render a specific kind of drawable.
	 */
	class three: virtual public neb::gfx::environ::base {
		public:
			typedef std::shared_ptr<neb::gfx::glsl::program::base>		program_shared;
			typedef std::shared_ptr<neb::gfx::camera::view::base>		view_shared;
			typedef std::shared_ptr<neb::gfx::camera::proj::base>		proj_shared;
		public:
			virtual void		init() = 0;

			//virtual void		step(gal::etc::timestep const & ts) = 0;

			virtual void		render(
					std::shared_ptr<neb::gfx::context::base> context) = 0;

		public:

			struct {
				program_shared			d3_;
				program_shared			d3_HF_;
				program_shared			d3_inst_;
			} programs_;


	};


}}}


#endif
