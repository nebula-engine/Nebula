#ifndef NEBULA_GRAPHICS_RENDER_DESC_HPP
#define NEBULA_GRAPHICS_RENDER_DESC_HPP

#include <neb/core/itf/shared.hpp>

#include <neb/gfx/camera/util/decl.hpp>
#include <neb/gfx/glsl/util/decl.hpp>

namespace neb {
	namespace gfx {

		class RenderDesc
		{
			public:
				RenderDesc(): v(0), p(0), d3(0), d3_inst(0) {}
				RenderDesc(
						camera::view::base* nv,
						camera::proj::base* np,
						glsl::program::base* nd3,
						glsl::program::base* nd3_HF,
						glsl::program::base* nd3_inst):
					v(nv), p(np), d3(nd3), d3_HF(nd3_HF), d3_inst(nd3_inst) {}

				camera::view::base*		v;
				camera::proj::base*		p;
				
				glsl::program::base*		d3;
				glsl::program::base*		d3_HF;
				glsl::program::base*		d3_inst;
				
		};
	}
}

#endif

