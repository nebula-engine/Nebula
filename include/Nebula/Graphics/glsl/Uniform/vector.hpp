#ifndef __UNIFORM_VECTOR_H__
#define __UNIFORM_VECTOR_H__

#include <memory>
#include <string>

#include <GLFW/glfw3.h>

//#include <PxPhysicsAPI.h>
#include <Nebula/Util/typedef.hpp>

//#include <math/mat44.hpp>
//#include <math/color.hpp>

namespace neb {
	namespace glsl {
		class program;
		namespace Uniform {
			namespace Vector {
				/** @brief %Array
				 * base class for array GLSL uniform
				 */
				class Base {
					public:
						Base(std::string, std::string);
						virtual ~Base() {}
						void				locate(std::shared_ptr<program>);
						/** @name Load
						 * @{
						 */
						virtual void			load(int, vec3 const &) { throw 0; }
						virtual void			load(int, vec4 const &) { throw 0; }
						virtual void			load(int, mat4 const &) { throw 0; }
						//virtual void			load(int, math::Color::color<float>) { throw 0; }
						//virtual void			load(int, math::Color::color<double>) { throw 0; }
						virtual void			load(int, int) { throw 0; }
						virtual void			load(int, float*) { throw 0; }
						virtual void			load(int, float) { throw 0; }
						/** @} */
					protected:
						enum { LEN = 100 };
						std::string		name1_;
						std::string		name2_;
						int			c_;
						GLuint			o_[LEN];

				};
				class Int: public neb::glsl::Uniform::Vector::Base {
					public:
						Int(std::string s1, std::string s2): Base(s1,s2) {}
						virtual void		load(int,int);
				};
				class Float: public neb::glsl::Uniform::Vector::Base {
					public:
						Float(std::string s1, std::string s2): Base(s1,s2) {}
						virtual void		load(int,float);
				};
				class Vec3: public neb::glsl::Uniform::Vector::Base {
					public:
						Vec3(std::string s1, std::string s2): Base(s1,s2) {}
						virtual void		load(int, float*);
						virtual void		load(int, vec3 const &);
				};
				class Vec4: public neb::glsl::Uniform::Vector::Base {
					public:
						Vec4(std::string s1, std::string s2): Base(s1,s2) {}
						virtual void		load(int, float*);
						virtual void		load(int, vec4 const &);
				};
				class Mat4: public neb::glsl::Uniform::Vector::Base {
					public:
						Mat4(std::string s1, std::string s2): Base(s1,s2) {}
						virtual void		load(int, mat4 const &);
				};
			}
		}
	}
}
#endif









