#ifndef __NEBULA_APP_H__
#define __NEBULA_APP_H__

#include <glutpp/window/window.h>

#include <neb/config.h>
#include <neb/network/server.h>
#include <neb/network/client.h>

namespace neb
{
	class app: public std::enable_shared_from_this<app>
	{
		public:
			app();
			void		init();

			glutpp::window::window_s	create_window(int, int, int, int, char const *);

			void		load_scene_local(glutpp::scene::desc_s);
			void		load_scene_remote(glutpp::scene::desc_s);

			void		load_layout(int,char const *);

			int		step(double);
			int		loop();
			
			neb::scene::scene_s	get_scene(int);
			
			int		activate_scene(int,int);
			int		deactivate_scene(int);
			int		activate_layout(int,int);
			int		deactivate_layout(int);


			void		send(std::shared_ptr<gal::network::message>);
			int		transmit_scenes(std::shared_ptr<neb::network::communicating>);
			
			
			glutpp::window::window_m		windows_;
			glutpp::gui::layout_m			layouts_;
			neb::scene::scene_m			scenes_;
			
			// network
			neb::network::server_s		server_;
			neb::network::client_s		client_;
	};
}

#endif





