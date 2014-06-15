#ifndef __UNIFORM_H__
#define __UNIFORM_H__

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
			namespace Scalar {
				/** @brief %base
				 *
				 * base class for scalar GLSL uniform
				 */
				class base {
					public:
						base(::std::string);
						virtual ~base() {}
						void			locate(::std::shared_ptr<program>);
						/** @name Load
						 * @{
						 */
						virtual void			load(vec3 const &) { throw 0; }
						virtual void			load(vec4 const &) { throw 0; }
						virtual void			load(mat4 const &) { throw 0; }
						//virtual void			load(math::Color::color<float>) { throw 0; }
						//virtual void			load(math::Color::color<double>) { throw 0; }
						virtual void			load(int) { throw 0; }
						virtual void			load(float*) { throw 0; }
						virtual void			load(double*) { throw 0; }
						virtual void			load(float) { throw 0; }
						virtual void			load(double) { throw 0; }
						/** @} */
					protected:
						::std::string		name_;
						GLint			o_;
				};

				class Int: public neb::glsl::Uniform::Scalar::base {
					public:
						Int(::std::string s): base(s) {}
						virtual void		load(int);
				};
				class Float: public neb::glsl::Uniform::Scalar::base {
					public:
						Float(::std::string s): base(s) {}
						virtual void		load(float);
				};
				class Double: public neb::glsl::Uniform::Scalar::base {
					public:
						Double(::std::string s): base(s) {}
						virtual void		load(double);
				};
				class Vec3: public neb::glsl::Uniform::Scalar::base {
					public:
						Vec3(::std::string s): base(s) {}
						virtual void		load(vec3 const &);
						virtual void		load(float*);
				};
				class Vec4: public neb::glsl::Uniform::Scalar::base {
					public:
						Vec4(::std::string s): base(s) {}
						virtual void		load(float*);
				};
				class DVec4: public neb::glsl::Uniform::Scalar::base {
					public:
						DVec4(::std::string s): base(s) {}
						virtual void		load(double*);
				};
				class Mat4: public neb::glsl::Uniform::Scalar::base {
					public:
						Mat4(::std::string s): base(s) {}
						virtual void		load(mat4 const &);
				};
				class Sampler2D: public neb::glsl::Uniform::Scalar::base {
					public:
						Sampler2D(::std::string s): base(s) {}
						virtual void		load(int);
				};
			}
		}
	}
}
#endif









