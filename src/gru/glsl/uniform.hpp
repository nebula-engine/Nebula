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
				/** @name Load Array Element
				 * @{
				 */
				void			load(int, math::mat44<float>);
				void			load(int, math::mat44<double>);
				void			load(int, math::Color::color<float>);
				void			load(int, math::Color::color<double>);
				void			load(int, int);
				void			load_4fv(int, double*);
				void			load_3fv(int, double*);
				void			load(int, float);
				void			load(int, double);
				/** @} */
				/** @name Load
				 * @{
				 */
				void			load(math::mat44<float>);
				void			load(math::mat44<double>);
				void			load(math::Color::color<float>);
				void			load(math::Color::color<double>);
				void			load(int);
				void			load_4fv(double*);
				void			load_3fv(double*);
				void			load(float);
				/** @} */

				char const *		s1_;
				char const *		s2_;
				int			c_;
				
				GLuint			o_[100];

		};
	}
}

#endif









