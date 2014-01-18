#ifndef __NEBULA_APP_H__
#define __NEBULA_APP_H__

#include <gal/flag.h>
#include <gal/timer/timer_set.h>

#include <glutpp/window/window.h>

#include <neb/config.h>
#include <neb/network/server.h>
#include <neb/network/client.h>

namespace neb {
	class app: public std::enable_shared_from_this<app>, public gal::flag<> {
		public:
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
			neb::actor::Base_s		get_actor(glutpp::actor::addr_s);
			
			int				activate_scene(int,int);
			int				deactivate_scene(int);
			int				activate_layout(int,int);
			int				deactivate_layout(int);
			
	
			// network
			void				reset_server(unsigned short);
			void				reset_client(char const *, unsigned short);		
			void				send_server(gal::network::message_s);
			void				send_client(gal::network::message_s);
			
			int				transmit_scenes(
					std::shared_ptr<neb::network::communicating>);
			
			void				recv_scene_create(gal::network::message_s);
			void				recv_actor_create(gal::network::message_s);
			void				recv_actor_update(gal::network::message_s);
			void				recv_actor_event(gal::network::message_s);
			void				recv_control_create(gal::network::message_s);
			void				recv_control_update(gal::network::message_s);
			

			void			f(unsigned int);
			unsigned int		f();
		public:
			unsigned int		flag_;

			glutpp::window::window_m	windows_;
			glutpp::gui::layout_m		layouts_;
			neb::scene::scene_m		scenes_;

			// timer
			gal::timer::timer_set		timer_set_;

		private:
			// network
			neb::network::server_s		server_;
			neb::network::client_s		client_;
	};
}

#endif





