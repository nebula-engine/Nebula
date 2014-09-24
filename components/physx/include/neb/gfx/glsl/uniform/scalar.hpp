#ifndef __UNIFORM_H__
#define __UNIFORM_H__

#include <memory>
#include <string>

#include <GLFW/glfw3.h>

#include <neb/core/util/typedef.hpp>

#include <neb/gfx/glsl/util/decl.hpp>

namespace neb { namespace gfx { namespace glsl { namespace uniform { namespace Scalar {
	/** @brief %base
	 *
	 * base class for scalar GLSL uniform
	 */
	class base {
		public:
			base(::std::string);
			virtual ~base() {}
			void			locate(std::shared_ptr<neb::gfx::glsl::program::base>);
			/** @name Load
			 * @{
			 */
			virtual void			load(vec3 const &) { throw 0; }
			virtual void			load(vec4 const &) { throw 0; }
			virtual void			load(mat4 const &) { throw 0; }
			virtual void			load(int) { throw 0; }
			virtual void			load(float*) { throw 0; }
			virtual void			load(double*) { throw 0; }
			virtual void			load(float) { throw 0; }
			virtual void			load(double) { throw 0; }
			virtual void			load_b(bool const &) {throw 0; }
			virtual void			load_b(bool &&) {throw 0; }
			/** @} */
		public:
			std::string		name_;
			GLint			o_;
	};

	class Bool: public neb::gfx::glsl::uniform::Scalar::base {
		public:
			Bool(std::string s): base(s) {}
			virtual void		load_b(bool const &);
			virtual void		load_b(bool &&);
	};
	class Int: public neb::gfx::glsl::uniform::Scalar::base {
		public:
			Int(::std::string s): base(s) {}
			virtual void		load(int);
	};
	class Float: public neb::gfx::glsl::uniform::Scalar::base {
		public:
			Float(::std::string s): base(s) {}
			virtual void		load(float);
	};
	class Double: public neb::gfx::glsl::uniform::Scalar::base {
		public:
			Double(::std::string s): base(s) {}
			virtual void		load(double);
	};
	class Vec3: public neb::gfx::glsl::uniform::Scalar::base {
		public:
			Vec3(::std::string s): base(s) {}
			virtual void		load(vec3 const &);
			virtual void		load(float*);
	};
	class Vec4: public neb::gfx::glsl::uniform::Scalar::base {
		public:
			Vec4(::std::string s): base(s) {}
			virtual void		load(vec4 const &);
			virtual void		load(float*);
	};
	class DVec4: public neb::gfx::glsl::uniform::Scalar::base {
		public:
			DVec4(::std::string s): base(s) {}
			virtual void		load(double*);
	};
	class Mat4: public neb::gfx::glsl::uniform::Scalar::base {
		public:
			Mat4(::std::string s): base(s) {}
			virtual void		load(mat4 const &);
	};
	class Sampler2D: public neb::gfx::glsl::uniform::Scalar::base {
		public:
			Sampler2D(::std::string s): base(s) {}
			virtual void		load(int);
	};
}}}}}

#endif









