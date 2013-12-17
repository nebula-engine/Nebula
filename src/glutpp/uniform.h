#ifndef __UNIFORM_H__
#define __UNIFORM_H__

#include <memory>

#include <GLFW/glfw3.h>

#include <math/mat44.h>

namespace glutpp
{
	class window;
	class scene;
	class uniform
	{
		public:
			uniform();
			void			init(std::shared_ptr<scene>, char const *);
			void			init(std::shared_ptr<scene>, char const *,char const *,int);
			void			locate();
			
			void			load(math::mat44);
			void			load_1i(int);
			void			load_4fv(float*);
			void			load_3fv(float*);

			void			load_matrix4fv(float*);
			void			load_1f(float);
			
			char			name_[128];
			GLuint			location_;
			
			std::weak_ptr<scene>	scene_;
	};
}

#endif
