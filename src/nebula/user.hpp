#ifndef __NEBULA_USER_H__
#define __NEBULA_USER_H__

#include <gru/master.hpp>
#include <gru/window/window.hpp>

#include <nebula/config.hpp>
//#include <nebula/camera/camera.hpp>

namespace neb {
	class user {
		public:
			user();
			void	init();
			void	connect(glutpp::window::window_s);
			void	set_control(neb::control::rigid_body::control_s);
			
			
			neb::control::rigid_body::control_s		control_;
			
	};
}

#endif
