#ifndef __NEBULA_APP_H__
#define __NEBULA_APP_H__

#include <fstream>

#include <boost/archive/polymorphic_xml_iarchive.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <Galaxy-Standard/shared.hpp>

#include <Galaxy-Network/decl.hpp>

#include <Nebula/free.hh>
#include <Nebula/Types.hh>
#include <Nebula/App/Util/Flag.hh>
#include <Nebula/App/__core.hpp>
#include <Nebula/App/__gfx.hpp>
#include <Nebula/App/__gfx_glsl.hpp>
#include <Nebula/App/__net.hpp>

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

namespace neb {
	namespace App {
		/** @brief Base
		 *
		 * final implementation
		 */
		class Base:
			virtual public neb::App::__gfx,
			virtual public neb::App::__gfx_glsl,
			virtual public neb::App::__core,
			virtual public neb::App::__net
		{
			public:
				friend void neb::init();
			public:
				Base();
				virtual ~Base();
			public:
				void						command(sp::shared_ptr<neb::gfx::GUI::Object::terminal> term, ::std::string);
			public:
				mat4						getPose();
				mat4						getPoseGlobal();

				static sp::shared_ptr<neb::App::Base>		global();

				void						loadXml(::std::string filename, neb::std::wrapper& w);

				sp::shared_ptr<neb::gfx::Window::Base>						get_window(GLFWwindow*);

			private:
			public:
				void					init();
				void					init_glew();
				void					step(neb::core::TimeStep const & ts);
				int					loop();

				void					set_should_release();


				/** @name %Network @{ */

				void					transmit_scenes(sp::shared_ptr<neb::Network::Communicating>);
				/** @} */

			public:
				static sp::shared_ptr<neb::App::Base>				g_app_;
				// network
				/** @todo make derived App classes for Server and Client??? */
				neb::App::Util::Flag						flag_;

			public:
				/** @name Font @{ */
				/** @} */
				/** @name Boost Asio @{ */
							/** @} */


		};
	}
}
#endif





