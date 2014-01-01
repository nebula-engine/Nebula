#ifndef __NEBULA_APP_H__
#define __NEBULA_APP_H__

#include <glutpp/window.h>

#include <neb/network/server.h>
#include <neb/network/client.h>
#include <neb/scene_desc.h>

namespace neb
{
	class scene;
	class view;
	
	class app: public std::enable_shared_from_this<app>
	{
		public:
			typedef std::map<int,std::shared_ptr<glutpp::window> >		map_window_t;
			typedef std::map<int,std::shared_ptr<glutpp::gui::layout> >	map_layout_t;
			typedef std::map<int,std::shared_ptr<neb::scene> >		map_scene_t;
			typedef std::shared_ptr<neb::network::server>			server_t;
			typedef std::shared_ptr<neb::network::client>			client_t;
			
			app();
			void		init();
		
			int		create_window(int name, int w, int h, int x, int y, char const * title);
			int		load_scene(int,char const *);
			int		load_scene(scene_desc*);
			int		load_layout(int,char const *);

			int		step(double);
			int		prepare();
			int		loop();
			
			int		activate_scene(int,int);
			int		deactivate_scene(int);
			int		activate_layout(int,int);
			int		deactivate_layout(int);
			
			
			int		transmit_scenes(std::shared_ptr<neb::network::communicating>);
			
			
			map_window_t	windows_;
			map_layout_t	layouts_;
			map_scene_t	scenes_;
			
			// network
			server_t	server_;
			client_t	client_;
	};
}

#endif
