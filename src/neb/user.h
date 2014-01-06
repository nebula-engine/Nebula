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
			void	connect(glutpp::window::window_shared);
			int	set_actor(neb::actor::Base_shared actor, neb::camera_type::e RIDEALONG);
			
			
			neb::actor::Base_weak				actor_;
			
			std::shared_ptr<glutpp::camera_control>		camera_control_;
			
			
		
	};
}

#endif
