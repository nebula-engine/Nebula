#ifndef __GLUTPP_SHADER_H__
#define __GLUTPP_SHADER_H__

#include <GLFW/glfw3.h>

namespace glutpp
{
namespace glsl
{
	class shader
	{
		public:
			void	load(const char * filename, GLenum shader_type);

			GLuint	o_;
	};
}
}

#endif
