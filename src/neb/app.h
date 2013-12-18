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
		

			int				load_scene(int,char const *);
			int				load_layout(int,char const *);

			void				step(double);


			
			int				activate_scene(int);
			int				deactivate_scene(int);
			int				activate_layout(int);
			int				deactivate_layout(int);
			
			
			std::shared_ptr<neb::window>	window_;

			
			//std::shared_ptr<neb::view>      		view_;

			std::map<int,std::shared_ptr<glutpp::gui::layout> >	layouts_;
			std::map<int,std::shared_ptr<neb::scene> >		scenes_;
			
			// network
			std::shared_ptr<neb::network::server>	server_;
			std::shared_ptr<neb::network::client>	client_;
	};
}

#endif
