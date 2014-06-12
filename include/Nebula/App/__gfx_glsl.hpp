#ifndef __NEBULA_APP___GFX_GLSL_H__
#define __NEBULA_APP___GFX_GLSL_H__

#include <fstream>

#include <boost/asio/io_service.hpp>
#include <boost/archive/polymorphic_xml_iarchive.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <Galaxy-Standard/shared.hpp>

#include <Galaxy-Network/decl.hpp>

#include <Nebula/free.hh>
#include <Nebula/Types.hh>
#include <Nebula/App/__base.hpp>
#include <Nebula/Graphics/Types.hh>

namespace neb {
	namespace App {
		class __gfx_glsl: virtual public neb::App::__base {
			public:
				typedef ::std::map<int, sp::shared_ptr<neb::glsl::program> >		map_program_type;

				friend class neb::gfx::Context::Base;
			protected:
				static sp::shared_ptr<neb::App::__gfx_glsl>		global();

				sp::shared_ptr<neb::glsl::program>			use_program(neb::program_name::e);
				sp::shared_ptr<neb::glsl::program>			get_program(neb::program_name::e);
			public:
				sp::shared_ptr<neb::glsl::program>			current_program();
				void							create_programs();


				map_program_type					programs_;
				sp::shared_ptr<neb::glsl::program>			current_;
		};
	}
}
#endif





