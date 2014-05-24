#ifndef __NEBULA_APP_H__
#define __NEBULA_APP_H__

#include <fstream>

#include <boost/asio/io_service.hpp>
#include <boost/archive/polymorphic_xml_iarchive.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <Nebula/Types.hh>
#include <Nebula/Util/Shared.hh>

#include <Nebula/App/Util/Flag.hh>
#include <Nebula/App/BaseFactory.hh>

#include <Nebula/network/Types.hh>

#include <Nebula/network2/server.hh>
#include <Nebula/network2/client.hh>

#include <Nebula/Message/Types.hh>

#include <Nebula/Scene/Util/Parent.hh>

#include <Nebula/Graphics/Window/Base.hh>
#include <Nebula/Graphics/Window/Util/Parent.hh>
#include <Nebula/Graphics/GUI/Layout/Util/Parent.hh>

#include <Nebula/Shape/Util/Types.hh>

namespace Neb {
	namespace App {
		class Base:
			virtual public Neb::Util::Shared,
			public Neb::App::BaseFactory,
			public Neb::Graphics::Window::Util::Parent,
			public Neb::Graphics::GUI::Layout::Util::Parent,
			public Neb::Scene::Util::Parent
		{
			public:
				typedef std::map< GLFWwindow*, Neb::Graphics::Window::Base_s >			glfwwindow_map_type;
			private:
				static void static_error_fun(int,char const *);
				static void static_window_pos_fun(GLFWwindow*,int,int);
				static void static_window_size_fun(GLFWwindow*,int,int);
				static void static_window_close_fun(GLFWwindow*);
				static void static_window_refresh_fun(GLFWwindow*);
				//static void static_window_focus_fun(GLFWwindow*,int);
				//static void static_window_iconify_fun(GLFWwindow*,int);
				//static void static_window_buffer_size_fun(GLFWwindow*,int,int);
				static void static_mouse_button_fun(GLFWwindow*,int,int,int);
				static void static_key_fun(GLFWwindow*,int,int,int,int);
			public:
				Base();
				virtual ~Base();
			public:
				void		command(std::string);
			public:
				std::shared_ptr<Neb::glsl::program>		use_program(Neb::program_name::e);
				std::shared_ptr<Neb::glsl::program>		get_program(Neb::program_name::e);
				std::shared_ptr<Neb::glsl::program>		current_program();
				void						create_programs();
			public:
				physx::PxTransform				getPose();
				physx::PxTransform				getPoseGlobal();

				/** @name Accessors @{ */
				static Neb::App::Base_s				globalBase();
				//Neb::Graphics::Window::Base_s			getWindowMain();
				//void						setWindowMain(Neb::Graphics::Window::Base_w);
				/** @} */
				/** @name Serialization @{ */
				template<class A> void				loadXml(std::string filename, A& a) {
					std::ifstream ifs;
					ifs.open(filename, std::ifstream::in);
					boost::archive::polymorphic_xml_iarchive ar(ifs);
					ar >> boost::serialization::make_nvp("archive",a);
				}
				/** @} */
				/*			template <class U> Neb::weak_ptr<U>				create_window(Neb::window::desc> wd) {
				//GLUTPP_DEBUG_0_FUNCTION;
				Neb::unique_ptr<U> u(new U(wd));
				auto g = reg(u);
				u->init();
				windows_[g] = u;

				auto wm = getWindowMain();
				if(!wm) {
				Main_Window(u);
				//fprintf(stderr, "window main set\n");
				//abort();
				} else {
				//fprintf(stderr, "window main already set\n");
				//abort();
				}	
				return u;
				}*/
				/** @name Search @{ */
				Neb::Actor::Base_w							getActor(Neb::Actor::Util::Address);
				/** @} */

				Neb::Graphics::Window::Base_s						get_window(GLFWwindow*);
				GLFWwindow*								reg(Neb::Graphics::Window::Base_s);

			public:
				/** @name Font @{ */
				FT_Library								ft_;
				/** @} */
				/** @name Boost Asio @{ */
				boost::asio::io_service							ios_;
				/** @} */




			private:
			public:
				struct flag {
					enum e {
						SHOULD_RELEASE = 1 << 0,			
					};
				};
				void					init();
				//Neb::Graphics::Window::Base_w			create_window(int, int, int, int, char const *);
				//Neb::Scene::Base_w				load_scene_local(Neb::Scene::desc_w);
				//Neb::Scene::Base_w				load_scene_remote(Neb::Scene::desc_w);
				void					load_layout(int,char const *);
				void					step(double const & time, double const & dt);
				int					loop();

				void					set_should_release();

				int					activate_scene(int,int);
				int					deactivate_scene(int);
				int					activate_layout(int,int);
				int					deactivate_layout(int);


				/** @name %Network @{ */
				void				reset_server(unsigned short);
				void				reset_client(char const *, unsigned short);		
				void				send_server(gal::network::omessage_s);
				void				send_client(gal::network::omessage_s);
				void				sendServer(Neb::Message::OBase_s message);
				void				sendClient(Neb::Message::OBase_s message);
				void				transmit_scenes(Neb::Network::Communicating_s);
				/** @} */
			private:
				// network
				/** @todo make derived App classes for Server and Client??? */
				Neb::Network::Server_s				server_;
				Neb::Network::Client_s				client_;


				Neb::App::Util::Flag						flag_;
				//GLFWwindow*							currentIdleWindow_;
				glfwwindow_map_type						windows_glfw_;
				static Neb::Graphics::Window::Base_w				window_main_;
				std::map<int, std::shared_ptr<Neb::glsl::program> >		programs_;
				std::shared_ptr<Neb::glsl::program>				current_;

		};
	}
}
#endif





