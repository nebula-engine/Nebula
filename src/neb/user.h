#ifndef __NEBULA_USER_H__
#define __NEBULA_USER_H__

#include <glutpp/master.h>
#include <glutpp/window/window.h>

#include <neb/camera.h>

namespace neb
{
	class user
	{
		public:
			user();
			void	init();
			void	connect(glutpp::window::window_s);
			int	set_actor(neb::actor::Base_s actor, neb::camera_type::e RIDEALONG);
			
			
			neb::actor::Base_w				actor_;
			
			std::shared_ptr<glutpp::camera_control>		camera_control_;
			
			
		
	};
}

#endif
