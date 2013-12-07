#ifndef __UNIFORM_H__
#define __UNIFORM_H__

#include <GL/glew.h>

#include <math/mat44.h>

namespace glutpp
{
	class window;
	class uniform
	{
		public:
			uniform();
			void		init(window*, char const *);
			void		init(window*, char const *,char const *,int);
			void		locate();
			
			void		load(math::mat44);
			void		load_1i(int);
			void		load_4fv(float*);
			void		load_3fv(float*);

			void		load_matrix4fv(float*);
			void		load_1f(float);
			
			char		name_[128];
			GLuint		location_;
	
			window*		window_;
	};
}

#endif
