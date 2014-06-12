#ifndef __NEBULA_APP_H__
#define __NEBULA_APP_H__

#include <fstream>

#include <boost/asio/io_service.hpp>
#include <boost/archive/polymorphic_xml_iarchive.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <Galaxy-Standard/shared.hpp>

#include <Galaxy-Network/decl.hpp>

#include <Nebula/free.hh>
#include <Nebula/Types.hh>
#include <Nebula/App/Util/Flag.hh>
#include <Nebula/Network/server.hh>
#include <Nebula/Network/client.hh>
#include <Nebula/Message/Types.hh>
#include <Nebula/Scene/Util/Parent.hh>

#include <Nebula/Graphics/Types.hh>
#include <Nebula/Graphics/Window/Base.hh>
#include <Nebula/Graphics/Window/Util/Parent.hh>
#include <Nebula/Graphics/GUI/Layout/Util/Parent.hh>
#include <Nebula/Shape/Util/Types.hh>
#include <Nebula/Util/wrapper.hpp>

namespace Neb {
	namespace App {
		class __gfx_glsl: virtual public Neb::App::__base {
			public:
				typedef std::map<int, std::shared_ptr<Neb::glsl::program> >		map_program_type;

				friend class Neb::Graphics::Context::Base;
			protected:
				static sp::shared_ptr<Neb::App::__gfx_glsl>		global();

				std::shared_ptr<Neb::glsl::program>			use_program(Neb::program_name::e);
				std::shared_ptr<Neb::glsl::program>			get_program(Neb::program_name::e);
			public:
				std::shared_ptr<Neb::glsl::program>			current_program();
				void							create_programs();


				map_program_type					programs_;
				std::shared_ptr<Neb::glsl::program>			current_;
		};
	}
}
#endif





