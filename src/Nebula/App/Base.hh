#ifndef __NEBULA_APP_H__
#define __NEBULA_APP_H__

#include <boost/asio/io_service.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <Nebula/Types.hh>
#include <Nebula/Util/Shared.hh>

#include <Nebula/App/Util/Flag.hh>

#include <Nebula/network2/server.hh>
#include <Nebula/network2/client.hh>

#include <Nebula/Scene/Util/Parent.hh>

#include <Nebula/Graphics/Window/Base.hh>
#include <Nebula/Graphics/Window/Util/Parent.hh>

#include <Nebula/Shape/Util/Types.hh>

namespace Neb {
	namespace App {
		class Base:
			virtual public Neb::Util::Shared,
			public Neb::Graphics::Window::Util::Parent,
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
				static Base_s					global();
				static void					global(Base_s);

				Neb::Graphics::Window::Base_s			getWindowMain();
				void						setWindowMain(Neb::Graphics::Window::Base_w);

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

				Neb::Graphics::Window::Base_w						get_window(GLFWwindow*);
				GLFWwindow*								reg(Neb::Graphics::Window::Base_s);

				//Neb::Actor::raw_factory_s						get_raw_factory();
				void						f(gal::flag::flag_type);
				gal::flag::flag_type				f();
			public:
				/** @name Font @{ */
				FT_Library								ft_;
				/** @} */
				/** @name Boost Asio @{ */
				boost::asio::io_service							ios_;
				/** @} */
				/** @brief Factories */
				struct {
					template<typename T> using pointer = std::shared_ptr<T>;

					typedef pointer< Neb::Factory<Neb::gui::object::object> >		Gui_Object;

					typedef pointer< Neb::Factory<Neb::Actor::Base> >			Actor_Base;

					typedef pointer< Neb::Factory<Neb::Shape::Base> >			Shape_Base;

					typedef pointer< Neb::Factory<Neb::Light::light> >			Light_Base;

					typedef pointer< Neb::Factory<Neb::Graphics::Window::Base> >		Window_Base;

					typedef pointer< Neb::Factory<Neb::Scene::Base> >			Scene_Base;

					Gui_Object			gui_object_;
					Actor_Base			actor_base_;
					Shape_Base			shape_base_;

					Light_Base			light_base_;

					Window_Base			window_base_;
	
					Scene_Base			scene_base_;
				} factories_;

			private:
			public:
				struct flag {
					enum e {
						SHOULD_RELEASE = 1 << 0,			
					};
				};
				void					init();
				Neb::Graphics::Window::Base_w			create_window(int, int, int, int, char const *);
				//Neb::Scene::Base_w				load_scene_local(Neb::Scene::desc_w);
				//Neb::Scene::Base_w				load_scene_remote(Neb::Scene::desc_w);
				void					load_layout(int,char const *);
				int					step(double);
				int					loop();

				/** @name Accessors @{ */
				Neb::Graphics::Window::Base_w			get_window(int);
				/** @} */

				void				set_should_release();

				int				activate_scene(int,int);
				int				deactivate_scene(int);
				int				activate_layout(int,int);
				int				deactivate_layout(int);


				/** @name %Network @{ */
				void				reset_server(unsigned short);
				void				reset_client(char const *, unsigned short);		
				void				send_server(boost::shared_ptr<gal::network::omessage>);
				void				send_client(boost::shared_ptr<gal::network::omessage>);
				int				transmit_scenes(boost::shared_ptr<gal::network::communicating>);
				/** @todo consider putting following functions into the messages themselves: would be cleaner that way. */
				void				recv_scene_create(std::shared_ptr<gal::network::message>);
				void				recv_actor_create(std::shared_ptr<gal::network::message>);
				void				recv_actor_update(std::shared_ptr<gal::network::message>);
				void				recv_actor_event(std::shared_ptr<gal::network::message>);
				void				recv_control_create(std::shared_ptr<gal::network::message>);
				void				recv_control_update(std::shared_ptr<gal::network::message>);
				/** @} */

			public:

				Neb::Map<Neb::Graphics::GUI::Layout::Base>			layouts_;
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

				/** %brief global app object */
				static Neb::App::Base_s						g_app_;
		};
	}
}
#endif





