#ifndef NEBULA_GRAPHICS_VIEWPORT_HPP
#define NEBULA_GRAPHICS_VIEWPORT_HPP

#include <GL/glew.h>

namespace Neb {
	namespace gfx {
		class Viewport {
			public:
				GLuint		x_, y_, w_, h_;
				GLfloat		aspect_;
		};
	}
}

#endif
