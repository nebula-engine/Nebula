#ifndef __GLUTPP_SHADER_H__
#define __GLUTPP_SHADER_H__


#include <GL/glew.h>
#include <GL/glut.h>

namespace glutpp
{
	class shader
	{
		public:
			GLuint	load(const char * filename, GLenum shader_type);

			GLuint	o_;
	};
}

#endif
