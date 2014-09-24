#ifndef __UNIFORM_VECTOR_H__
#define __UNIFORM_VECTOR_H__

#include <memory>
#include <string>

#include <GLFW/glfw3.h>

#include <neb/core/util/typedef.hpp>

#include <neb/gfx/glsl/util/decl.hpp>

namespace neb { namespace gfx { namespace glsl { namespace uniform { namespace Vector {
	/** @brief %Array
	 * base class for array GLSL uniform
	 */
	class base {
		public:
			base(std::string);
			virtual ~base() {}
			void				locate(std::shared_ptr<neb::gfx::glsl::program::base>);
			/** @name Load
			 * @{
			 */
			virtual void			load(int, vec3 const &) { throw 0; }
			virtual void			load(int, vec4 const &) { throw 0; }
			virtual void			load(int, mat4 const &) { throw 0; }
			virtual void			load(int, int) { throw 0; }
			virtual void			load(int, float*) { throw 0; }
			virtual void			load(int, float) { throw 0; }
			/** @} */
		public:
			enum { LEN = 100 };
			std::string		name_;
			int			c_;
			GLuint			o_[LEN];

	};
	class Int: public neb::gfx::glsl::uniform::Vector::base {
		public:
			Int(std::string s): base(s) {}
			virtual void		load(int,int);
	};
	class Float: public neb::gfx::glsl::uniform::Vector::base {
		public:
			Float(std::string s): base(s) {}
			virtual void		load(int,float);
	};
	class Vec3: public neb::gfx::glsl::uniform::Vector::base {
		public:
			Vec3(std::string s): base(s) {}
			virtual void		load(int, float*);
			virtual void		load(int, vec3 const &);
	};
	class Vec4: public neb::gfx::glsl::uniform::Vector::base {
		public:
			Vec4(std::string s): base(s) {}
			virtual void		load(int, float*);
			virtual void		load(int, vec4 const &);
	};
	class mat4: public neb::gfx::glsl::uniform::Vector::base {
		public:
			mat4(std::string s): base(s) {}
			virtual void		load(int, glm::mat4 const &);
	};
}}}}}

#endif









