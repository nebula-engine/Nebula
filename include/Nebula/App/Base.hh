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
		class __base {
			public:
			
		};
		/** @brief gfx
		 * 
		 * graphics and window handling
		 */
		class __gfx: virtual public Neb::App::__base {
			public:
				typedef std::map< GLFWwindow*, Neb::Graphics::Window::Base_s >			glfwwindow_map_type;

				static void			static_error_fun(int,char const *);
				static void			static_window_pos_fun(GLFWwindow*,int,int);
				static void			static_window_size_fun(GLFWwindow*,int,int);
				static void			static_window_close_fun(GLFWwindow*);
				static void			static_window_refresh_fun(GLFWwindow*);
				//static void static_window_focus_fun(GLFWwindow*,int);
				//static void static_window_iconify_fun(GLFWwindow*,int);
				//static void static_window_buffer_size_fun(GLFWwindow*,int,int);
				static void			static_mouse_button_fun(GLFWwindow*,int,int,int);
				static void			static_key_fun(GLFWwindow*,int,int,int,int);
			public:

				//GLFWwindow*								currentIdleWindow_;
				glfwwindow_map_type							windows_glfw_;
				
				std::map<int, std::shared_ptr<Neb::glsl::program> >			programs_;
				std::shared_ptr<Neb::glsl::program>					current_;

				FT_Library								ft_;
		};
		/** @brief Base
		 *
		 * final implementation
		 */
		class Base:
			virtual public Neb::App::__gfx,
			virtual public Neb::Graphics::Window::Util::Parent,
			virtual public Neb::Graphics::GUI::Layout::Util::Parent,
			virtual public Neb::Scene::Util::Parent
		{
			public:
								friend void Neb::init();
			public:
				Base();
				virtual ~Base();
			public:
				void						command(sp::shared_ptr<Neb::Graphics::GUI::Object::terminal> term, std::string);
			public:
				std::shared_ptr<Neb::glsl::program>		use_program(Neb::program_name::e);
				std::shared_ptr<Neb::glsl::program>		get_program(Neb::program_name::e);
				std::shared_ptr<Neb::glsl::program>		current_program();
				void						create_programs();
			public:
				mat4						getPose();
				mat4						getPoseGlobal();

				/** @name Accessors @{ */
				static Neb::App::Base_s				globalBase();
				//Neb::Graphics::Window::Base_s			getWindowMain();
				//void						setWindowMain(Neb::Graphics::Window::Base_w);
				/** @} */
				/** @name Serialization @{ */
				void						loadXml(std::string filename, neb::std::wrapper& w);
				/** @} */

				Neb::Graphics::Window::Base_s						get_window(GLFWwindow*);

			private:
			public:
				void					init();
				void					init_glew();
				void					load_layout(int,char const *);
				void					step(Neb::Core::TimeStep const & ts);
				int					loop();

				void					set_should_release();

				int					activate_scene(int,int);
				int					deactivate_scene(int);
				int					activate_layout(int,int);
				int					deactivate_layout(int);


				/** @name %Network @{ */
				void					reset_server(ip::tcp::endpoint const & endpoint);
				void					reset_client(ip::tcp::resolver::iterator endpoint_iterator);

				void					sendServer(sp::shared_ptr< gal::net::omessage >);
				void					sendServer(sp::shared_ptr< Neb::Message::OBase > message);
				void					sendClient(sp::shared_ptr< gal::net::omessage >);
				void					sendClient(sp::shared_ptr< Neb::Message::OBase > message);

				void					transmit_scenes(Neb::Network::Communicating_s);
				/** @} */

			public:
				static sp::shared_ptr<Neb::App::Base>				g_app_;
				// network
				/** @todo make derived App classes for Server and Client??? */
				sp::shared_ptr<Neb::Network::Server>				server_;
				sp::shared_ptr<Neb::Network::Client>				client_;
				Neb::App::Util::Flag						flag_;
				static Neb::Graphics::Window::Base_w				window_main_;

			public:
				/** @name Font @{ */
				/** @} */
				/** @name Boost Asio @{ */
				boost::asio::io_service							ios_;
				/** @} */


		};
	}
}
#endif





