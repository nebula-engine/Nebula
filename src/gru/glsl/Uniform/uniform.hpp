#ifndef __UNIFORM_H__
#define __UNIFORM_H__

#include <memory>

#include <GLFW/glfw3.h>

#include <math/mat44.hpp>
#include <math/color.hpp>

namespace glutpp {
	namespace glsl {
		class program;

		namespace Uniform {
			namespace Scalar {
				/** @brief %Base
				 *
				 * base class for scalar GLSL uniform
				 */
				class Base {
					public:
						Base();
						virtual ~Base();
						void			init(char const *);
						void			locate(std::shared_ptr<program>);
						/** @name Load
						 * @{
						 */
						virtual void			load(math::mat44<float>) { throw 0; }
						virtual void			load(math::mat44<double>) { throw 0; }
						virtual void			load(math::Color::color<float>) { throw 0; }
						virtual void			load(math::Color::color<double>) { throw 0; }
						virtual void			load(int) { throw 0; }
						virtual void			load_4fv(double*) { throw 0; }
						virtual void			load_3fv(double*) { throw 0; }
						virtual void			load(float) { throw 0; }
						virtual void			load(double) { throw 0; }
						/** @} */

						std::string		name_;
						GLuint			o_;
				};

				class Int: public glutpp::glsl::Uniform::Scalar::Base {
					public:
						virtual void		load(int);
				};
				class Float: public glutpp::glsl::Uniform::Scalar::Base {
					public:
						virtual void		load(float);
				};
				class Double: public glutpp::glsl::Uniform::Scalar::Base {
					public:
						virtual void		load(double);
				};
				class Vec3: public glutpp::glsl::Uniform::Scalar::Base {
					public:
						virtual void		load_3fv(double*);
				};
				class DVec3: public glutpp::glsl::Uniform::Scalar::Base {
					public:
						virtual void		load_3fv(double*);
				};
			}
			namespace Vector {
				/** @brief %Array
				 * base class for array GLSL uniform
				 */
				class Base {
					public:
						Base();
						virtual ~Base();
						void			init(std::string, std::string);
						void			locate(std::shared_ptr<program>);
						/** @name Load
						 * @{
						 */
						virtual void			load(int, math::mat44<float>) { throw 0; }
						virtual void			load(int, math::mat44<double>) { throw 0; }
						virtual void			load(int, math::Color::color<float>) { throw 0; }
						virtual void			load(int, math::Color::color<double>) { throw 0; }
						virtual void			load(int, int) { throw 0; }
						virtual void			load_4fv(int, double*) { throw 0; }
						virtual void			load_3fv(int, double*) { throw 0; }
						virtual void			load(int, float) { throw 0; }
						virtual void			load(int, double) { throw 0; }
						/** @} */

						std::string		name1_;
						std::string		name2_;
						int			c_;
						GLuint			o_[100];

				};
				class Int: public glutpp::glsl::Uniform::Vector::Base {
					public:
						virtual void		load(int,int);
				};
				class Float: public glutpp::glsl::Uniform::Vector::Base {
					public:
						virtual void		load(int,float);
				};
				class Double: public glutpp::glsl::Uniform::Vector::Base {
					public:
						virtual void		load(int,double);
				};
				class Vec3: public glutpp::glsl::Uniform::Vector::Base {
					public:
						virtual void		load_3fv(int, double*);
				};
				class DVec3: public glutpp::glsl::Uniform::Vector::Base {
					public:
						virtual void		load_3fv(int ,double*);
				};
			}
		}
	}
}
#endif









