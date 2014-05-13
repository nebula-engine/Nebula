#ifndef __NEBULA_APP_H__
#define __NEBULA_APP_H__

#include <boost/asio/io_service.hpp>

#include <Nebula/Graphics/window/window.hh>

#include <Nebula/Types.hh>
#include <Nebula/Util/Shared.hh>
#include <Nebula/network2/server.hh>
#include <Nebula/network2/client.hh>


namespace Neb {
	class App: virtual public Neb::Shared, public gal::flag {
		public:
			typedef std::map< GLFWwindow*, Neb::window::window_s >			window_map_type;
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
			App();
			~App();
		public:
			void		command(std::string);
		public:
			std::shared_ptr<Neb::glsl::program>		use_program(Neb::program_name::e);
			std::shared_ptr<Neb::glsl::program>		get_program(Neb::program_name::e);
			std::shared_ptr<Neb::glsl::program>		current_program();
			void						create_programs();
		public:
			static App_s					global();
			static void					global(App_s);
			
			Neb::weak_ptr<Neb::window::window>				getWindowMain();
			void								setWindowMain(Neb::window::window_w);
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
			Neb::weak_ptr<Neb::Actor::Base>					getActor(Neb::Actor::Address);


			Neb::weak_ptr<Neb::window::window>					get_window(GLFWwindow*);
			GLFWwindow*								reg(Neb::window::window_s);

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
				template<typename T>
				using pointer = std::shared_ptr<T>;
				
				typedef pointer< Neb::Factory<Neb::gui::object::object> >		Gui_Object;
				typedef pointer< Neb::Factory<Neb::Actor::raw> >			Actor_Raw;
				typedef pointer< Neb::Factory<Neb::Actor::Base> >			Actor_Base;
				typedef pointer< Neb::Factory<Neb::Shape::Raw> >			Shape_Raw;
				typedef pointer< Neb::Factory<Neb::Shape::shape> >			Shape_Base;
				typedef pointer< Neb::Factory<Neb::Light::light> >			Light_Base;
				typedef pointer< Neb::Factory<Neb::window::window> >			Window;

				//typedef pointer< Neb::Factory<Neb::Scene::Raw> >			SceneRaw;

				Gui_Object			gui_object_;
				Actor_Raw			actor_raw_;
				Actor_Base			actor_base_;
				Shape_Raw			shape_raw_;
				Shape_Base			shape_base_;

				Light_Base			light_base_;

				//SceneRaw			scene_raw_;
			} factories_;

		private:
		public:
			struct flag {
				enum e {
					SHOULD_RELEASE = 1 << 0,			
				};
			};
			void					init();
			Neb::window::window_w			create_window(int, int, int, int, char const *);
			//Neb::Scene::Base_w				load_scene_local(Neb::Scene::desc_w);
			//Neb::Scene::Base_w				load_scene_remote(Neb::Scene::desc_w);
			void					load_layout(int,char const *);
			int					step(double);
			int					loop();

			/** @name Accessors @{ */
			Neb::window::window_w			get_window(int);
			Neb::Scene::Base_w			get_scene(int);
			Neb::Scene::Base_w			get_scene(Neb::Scene::Address);
			Neb::Actor::Base_w			get_actor(Neb::Actor::addr);
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
			Neb::Map<Neb::window::window>			windows_;
			Neb::Map<Neb::gui::layout>			layouts_;
			Neb::Map<Neb::Scene::Base>			scenes_;
		private:
			// network
			Neb::unique_ptr<Neb::network::server>		server_;
			Neb::unique_ptr<Neb::network::client>		client_;


			unsigned int							flag_;
			//GLFWwindow*							currentIdleWindow_;
			window_map_type							windows_glfw_;
			static Neb::window::window_w					window_main_;
			std::map<int, std::shared_ptr<Neb::glsl::program> >		programs_;
			std::shared_ptr<Neb::glsl::program>				current_;
			static Neb::App_s						g_master_;
	};
}

#endif





