#ifndef __NEBULA_APP_H__
#define __NEBULA_APP_H__

//#include <galaxy/flag.hpp>
//#include <galaxy/timer/timer_set.hpp>

#include <gru/window/window.hpp>

#include <nebula/config.hpp>
#include <nebula/network/server.hpp>
#include <nebula/network/client.hpp>

namespace neb {
	class app: public std::enable_shared_from_this<app>, public gal::flag<> {
		public:
			struct flag {
				enum e {
					SHOULD_RELEASE = 1 << 0,			
				};
			};
			app();
			void				init();

			glutpp::window::window_s	create_window(int, int, int, int, char const *);

			neb::scene::scene_s		load_scene_local(glutpp::scene::desc_s);
			neb::scene::scene_s		load_scene_remote(glutpp::scene::desc_s);

			void				load_layout(int,char const *);

			int				step(double);
			int				loop();

			glutpp::window::window_s	get_window(int);
			neb::scene::scene_s		get_scene(int);
			neb::scene::scene_s		get_scene(glutpp::scene::addr_s);
			neb::Actor::Base_s		get_actor(glutpp::actor::addr_s);

			void				set_should_release();

			int				activate_scene(int,int);
			int				deactivate_scene(int);
			int				activate_layout(int,int);
			int				deactivate_layout(int);


			// network
			void				reset_server(unsigned short);
			void				reset_client(char const *, unsigned short);		
			void				send_server(boost::shared_ptr<gal::network::message>);
			void				send_client(boost::shared_ptr<gal::network::message>);

			int				transmit_scenes(boost::shared_ptr<neb::network::communicating>);

			void				recv_scene_create(	std::shared_ptr<gal::network::message>);
			void				recv_actor_create(	std::shared_ptr<gal::network::message>);
			void				recv_actor_update(	std::shared_ptr<gal::network::message>);
			void				recv_actor_event(	std::shared_ptr<gal::network::message>);
			void				recv_control_create(	std::shared_ptr<gal::network::message>);
			void				recv_control_update(	std::shared_ptr<gal::network::message>);


			void				f(unsigned int);
			unsigned int			f();
		public:
			unsigned int			flag_;

			Neb::Map<glutpp::window::window>	windows_;
			Neb::Map<glutpp::gui::layout>		layouts_;
			Neb::Map<neb::scene::scene>		scenes_;

			// timer
			//gal::timer::timer_set		timer_set_;

		private:
			// network
			neb::network::server_s		server_;
			neb::network::client_s		client_;
	};
}

#endif





