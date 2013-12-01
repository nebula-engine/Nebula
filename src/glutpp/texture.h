#ifndef __GRU_TEXTURE_H__
#define __GRU_TEXTURE_H__

#include <functional>

#include <math/mat44.h>
#include <math/vec4.h>
#include <math/vec3.h>

namespace glutpp
{
	class texture
	{
		public:
			texture();
			~texture();
			void			init(int,int);
			void			load_png(char const *);
			void			bind();
			
			GLuint			o_;
	};
}

#endif








