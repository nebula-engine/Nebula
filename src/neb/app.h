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
			void				load(char const *);
			void				step(double);

			std::shared_ptr<neb::window>	window_;

			
			std::shared_ptr<neb::view>      view_;
			std::shared_ptr<neb::scene>     scene_;
	
			// network
			std::shared_ptr<neb::network::server>	server_;
			std::shared_ptr<neb::network::client>	client_;
	};
}

#endif
