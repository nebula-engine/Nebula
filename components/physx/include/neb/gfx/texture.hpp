#ifndef __GRU_TEXTURE_H__
#define __GRU_TEXTURE_H__

#include <functional>
#include <map>

#define PNG_SKIP_SETJMP_CHECK
#include <png.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <gal/etc/slots.hpp>

#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/drawable/base.hpp>

namespace neb { namespace gfx {
	class texture: public neb::gfx::drawable::base {
		public:

			typedef std::map< neb::gfx::context::base*, GLuint >		map_t;

			static std::shared_ptr<neb::gfx::texture>	makePNG(std::string filename);

			texture();
			~texture();
			virtual void		init() {}
			virtual void		step(gal::etc::timestep const &) {}
			void			init_shadow(int,int, std::shared_ptr<neb::gfx::context::base> context);

			int			load_png(std::string filename);

			GLuint			init_buffer(std::shared_ptr<neb::gfx::context::base> context);
			GLuint			genAndBind(std::shared_ptr<neb::gfx::context::base> context);


			void			bind(neb::gfx::glsl::program::base const * const &);
			
			// for visualizing the contents
			virtual void			draw(RenderDesc const &);

			png_uint_32		w_;
			png_uint_32		h_;

			png_byte*		png_image_data_;
			
			
			std::shared_ptr<gal::etc::slots>		layer_slots_;

			//map_t			buffers_;
			GLuint			o_;
			GLenum			target_;
	};
}}

#endif








