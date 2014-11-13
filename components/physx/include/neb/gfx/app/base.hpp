#ifndef NEB_GFX_APP_BASE_HPP
#define NEB_GFX_APP_BASE_HPP

#include <neb/core/app/__core.hpp>

#include <neb/gfx/app/__gfx.hpp>
#include <neb/gfx/app/__gfx_glsl.hpp>

namespace neb {
	namespace gfx {
		namespace app {
			/** @brief base */
			class base:
				virtual public neb::app::__core,
				virtual public neb::gfx::app::__gfx,
				virtual public neb::gfx::app::__gfx_glsl
			{
				public:
					static weak_ptr<neb::gfx::app::base>		initialize();
				protected:
					virtual void					__init();
				public:
					virtual void					release();
					virtual void					step(gal::etc::timestep const & ts);

					void						loop();
			};
		}
	}
}

#endif
