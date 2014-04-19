#ifndef __UNIFORM_H__
#define __UNIFORM_H__

#include <memory>

#include <GLFW/glfw3.h>

#include <math/mat44.hpp>
#include <math/color.hpp>

namespace glutpp {
	namespace glsl {
		class program;
		class uniform {
			public:
				uniform();
				void			init(char const *);
				void			init(char const *,char const *,int);
				void			locate(std::shared_ptr<program>);

				void			load(int, math::mat44);
				void			load(int, math::color);
				void			load(int, int);
				void			load_4fv(int, float*);
				void			load_3fv(int, float*);
				void			load(int, float);

				void			load(math::mat44);
				void			load(math::color);
				void			load(int);
				void			load_4fv(float*);
				void			load_3fv(float*);
				void			load(float);

				char const *		s1_;
				char const *		s2_;
				int			c_;
				
				GLuint			o_[100];

		};
	}
}

#endif
