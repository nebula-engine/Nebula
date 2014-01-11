#ifndef __GRU_TEXTURE_H__
#define __GRU_TEXTURE_H__

#include <functional>


#include <GLFW/glfw3.h>


#include <math/mat44.h>
#include <math/vec4.h>
#include <math/vec3.h>

#include <glutpp/config.h>

namespace glutpp
{
	class texture
	{
		public:
			texture();
			~texture();
			void			init(glutpp::window::window_s);
			void			init_shadow(int,int);
			int			load_png(char const *);
			void			bind();
			
			GLint			w_;
			GLint			h_;
			GLuint			o_;
			
			glutpp::window::window_s		window_;
	};
}

#endif








