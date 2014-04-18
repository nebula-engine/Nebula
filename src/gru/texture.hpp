#ifndef __GRU_TEXTURE_H__
#define __GRU_TEXTURE_H__

#include <functional>


#include <GLFW/glfw3.h>


#include <math/mat44.h>
#include <math/vec4.h>
#include <math/vec3.h>

#include <gru/config.hpp>

namespace glutpp
{
	/*template<typename WINDOW>*/ class texture
	{
		public:
			//typedef std::shared_ptr<WINDOW>		WINDOW_S;
			//typedef std::weak_ptr<WINDOW>		WINDOW_W;
			

			texture();
			~texture();
			//void			init(WINDOW_S);
			void			init_shadow(int,int);
			int			load_png(char const *);
			void			bind();
			
			GLint			w_;
			GLint			h_;
			GLuint			o_;
			
//			WINDOW_W		window_;
	};
}

#endif








