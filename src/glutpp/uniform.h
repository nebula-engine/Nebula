#ifndef __UNIFORM_H__
#define __UNIFORM_H__

#include <GL/glew.h>

namespace glutpp
{
	class uniform
	{
		public:

			void		init(GLuint program, char const *);
			void		load(math::mat44);

			GLuint		location_;



	};
}

#endif
