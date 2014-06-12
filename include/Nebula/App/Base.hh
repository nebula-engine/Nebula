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

		class __core:
			virtual public neb::App::__base,
			virtual public neb::gfx::GUI::Layout::Util::Parent,
			virtual public neb::Scene::Util::Parent
		{



		};


		class __net:
			virtual public neb::App::__base
		{

			void					reset_server(ip::tcp::endpoint const & endpoint);
			void					reset_client(ip::tcp::resolver::iterator endpoint_iterator);

			void					sendServer(sp::shared_ptr< gal::net::omessage >);
			void					sendServer(sp::shared_ptr< neb::Message::OBase > message);
			void					sendClient(sp::shared_ptr< gal::net::omessage >);
			void					sendClient(sp::shared_ptr< neb::Message::OBase > message);


			sp::shared_ptr<neb::Network::Server>				server_;
			sp::shared_ptr<neb::Network::Client>				client_;

		}



		/** @brief Base
		 *
		 * final implementation
		 */
		class Base:
			virtual public neb::App::__gfx,
			virtual public neb::App::__gfx_glsl,
			virtual public neb::App::__core,
		{
			public:
				friend void neb::init();
			public:
				Base();
				virtual ~Base();
			public:
				void						command(sp::shared_ptr<neb::gfx::GUI::Object::terminal> term, std::string);
			public:
				mat4						getPose();
				mat4						getPoseGlobal();

				static sp::shared_ptr<neb::App::Base>		global();

				void						loadXml(std::string filename, neb::std::wrapper& w);

				neb::gfx::Window::Base_s						get_window(GLFWwindow*);

			private:
			public:
				void					init();
				void					init_glew();
				void					step(neb::core::TimeStep const & ts);
				int					loop();

				void					set_should_release();


				/** @name %Network @{ */

				void					transmit_scenes(sp::shared_ptr<neb::Network::Communicating>;
				/** @} */

			public:
				static sp::shared_ptr<neb::App::Base>				g_app_;
				// network
				/** @todo make derived App classes for Server and Client??? */
				neb::App::Util::Flag						flag_;
				static neb::gfx::Window::Base_w				window_main_;

			public:
				/** @name Font @{ */
				/** @} */
				/** @name Boost Asio @{ */
							/** @} */


		};
	}
}
#endif





