#ifndef __NEBULA_APP___GFX_GLSL_H__
#define __NEBULA_APP___GFX_GLSL_H__

#include <fstream>

#include <boost/asio/io_service.hpp>
#include <boost/archive/polymorphic_xml_iarchive.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <gal/itf/shared.hpp>

#include <neb/core/util/decl.hpp>
#include <neb/core/app/__base.hpp>
#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/glsl/util/decl.hpp>


namespace neb { namespace gfx { namespace app {
	class __gfx_glsl:
		virtual public neb::core::app::__base
	{
		public:
			//typedef std::map<int, std::shared_ptr<neb::gfx::glsl::program::base> >		map_program_type;
			friend class neb::gfx::environ::base;
			friend class neb::gfx::environ::two;
			friend class neb::gfx::environ::three;
		public:
			static std::weak_ptr<neb::gfx::app::__gfx_glsl>		global();
		protected:
			void							__init();
			//std::shared_ptr<neb::gfx::glsl::program::base>		use_program(neb::program_name::e);
			//std::shared_ptr<neb::gfx::glsl::program::base>		get_program(neb::program_name::e);
		public:
			//std::shared_ptr<neb::gfx::glsl::program::base>		current_program();
			void							create_programs();
			//map_program_type					programs_;
			//std::shared_ptr<neb::gfx::glsl::program::base>		current_;
			std::shared_ptr<neb::gfx::glsl::program::base>		program_text_;
			std::shared_ptr<neb::gfx::glsl::program::base>		program_tex_;
			std::shared_ptr<neb::gfx::glsl::program::base>		program_simple3_;

	};
}}}

#endif





