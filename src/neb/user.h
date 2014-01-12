#ifndef __NEBULA_USER_H__
#define __NEBULA_USER_H__

#include <glutpp/master.h>
#include <glutpp/window/window.h>

#include <neb/config.h>
#include <neb/camera.h>

namespace neb
{
	class user
	{
		public:
			user();
			void	init();
			void	connect(glutpp::window::window_s);
			void	set_control(neb::actor::rigid_body::control_s);
			
			
			neb::actor::rigid_body::control_s		control_;
			
	};
}

#endif
