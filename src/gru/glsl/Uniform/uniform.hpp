#ifndef __UNIFORM_H__
#define __UNIFORM_H__

#include <memory>

#include <GLFW/glfw3.h>

#include <math/mat44.hpp>
#include <math/color.hpp>

namespace glutpp {
	namespace glsl {
		class program;
		namespace Base {
			/** @brief %Base
			 *
			 * base GLSL uniform class
			 */
			class Base {
				public:
					uniform();
					virtual ~uniform;
					void			init(char const *);
					void			init(char const *,char const *,int);
					void			locate(std::shared_ptr<program>);
					/** @name Load Array Element
					 * @{
					 */
					virtual void			load(int, math::mat44<float>) { throw 0; }
					virtual void			load(int, math::mat44<double>);
					virtual void			load(int, math::Color::color<float>);
					virtual void			load(int, math::Color::color<double>);
					virtual void			load(int, int);
					virtual void			load_4fv(int, double*);
					virtual void			load_3fv(int, double*);
					virtual void			load(int, float);
					virtual void			load(int, double);
					/** @} */
					/** @name Load
					 * @{
					 */
					virtual void			load(math::mat44<float>);
					virtual void			load(math::mat44<double>);
					virtual void			load(math::Color::color<float>);
					virtual void			load(math::Color::color<double>);
					virtual void			load(int);
					virtual void			load_4fv(double*);
					virtual void			load_3fv(double*);
					virtual void			load(float);
					virtual void			load(double);
					/** @} */

					char const *		s1_;
					char const *		s2_;
					int			c_;

					GLuint			o_[100];

			};
			class Int: public glutpp::glsl::Uniform::Base {
				public:
					virtual void		load(int);
					virtual void		load(int,int);
			}
		}
	}
}
#endif









