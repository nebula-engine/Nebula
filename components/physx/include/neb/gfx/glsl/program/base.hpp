#ifndef __DRAW_H__
#define __DRAW_H__

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <map>
#include <vector>

#include <neb/core/util/decl.hpp>
#include <neb/core/util/typedef.hpp>

#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/glsl/util/decl.hpp>
#include <neb/gfx/glsl/program/util/flag.hpp>

namespace neb { namespace gfx { namespace glsl { namespace program {
	class base: public std::enable_shared_from_this<base> {
		public:
			
			enum {
				VERT = 0,
				FRAG = 1
			};

			base(std::string);
			virtual ~base();
			
			virtual void		init();
			void			restoreDefaultShaderFlags();
			void			add_shader(std::string, GLenum);
			void			add_shaders(std::vector<neb::gfx::glsl::shader>);
			void			compile();
			void			use() const;
			void			locate();
			void			scanUniforms();

			GLuint			o_;
			std::string		name_;


			int			shader_[2];

			GLint			attrib_table_[neb::gfx::glsl::attribs::COUNT];
			GLint			uniform_table_[neb::gfx::glsl::uniforms::COUNT];

			neb::gfx::glsl::program::util::flag_shader	flag_shader_;
			neb::gfx::glsl::program::util::flag_shader	flag_shader_def_;
	};
}}}}

#endif
