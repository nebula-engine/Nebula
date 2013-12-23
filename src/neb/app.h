#ifndef __NEBULA_APP_H__
#define __NEBULA_APP_H__

#include <neb/window.h>

#include <neb/network/server.h>
#include <neb/network/client.h>

namespace neb
{
	class scene;
	class view;
	
	class app: public std::enable_shared_from_this<app>
	{
		public:
			app();
			void				init();
		
			int				create_window(int name, int w, int h, int x, int y, char const * title);
			int				load_scene(int,char const *);
			int				load_layout(int,char const *);

			void				step(double);


			
			int				activate_scene(int,int);
			int				deactivate_scene(int);
			int				activate_layout(int,int);
			int				deactivate_layout(int);
			
			
			std::map<int,std::shared_ptr<neb::window> >		windows_;
			std::map<int,std::shared_ptr<glutpp::gui::layout> >	layouts_;
			std::map<int,std::shared_ptr<neb::scene> >		scenes_;
			
			// network
			std::shared_ptr<neb::network::server>	server_;
			std::shared_ptr<neb::network::client>	client_;
	};
}

#endif
