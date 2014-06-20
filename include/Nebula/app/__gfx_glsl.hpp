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
#include <Nebula/util/decl.hpp>
#include <Nebula/app/__base.hpp>
#include <Nebula/gfx/util/decl.hpp>

namespace neb {
	namespace app {
		class __gfx_glsl: virtual public neb::app::__base {
			public:
				typedef ::std::map<int, sp::shared_ptr<neb::glsl::program> >		map_program_type;

				friend class neb::gfx::environ::base;
				friend class neb::gfx::environ::two;
				friend class neb::gfx::environ::three;

			protected:
				static sp::shared_ptr<neb::app::__gfx_glsl>		global();

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





