#ifndef __NEBULA_USER_H__
#define __NEBULA_USER_H__

#include <glutpp/master.h>
#include <glutpp/window.h>

#include <neb/camera.h>

namespace neb
{
	namespace actor
	{
		class Base;
	}
	class user
	{
		public:
			user();
			void	init();
			void	connect(std::shared_ptr<glutpp::window>);
			int	set_actor(std::shared_ptr<neb::actor::Base> actor, neb::camera_type::e RIDEALONG);
			
			
			std::shared_ptr<neb::actor::Base>		actor_;
			
			std::shared_ptr<glutpp::camera_control>		camera_control_;
			
			
			
			struct
			{
				key_fun_c		key_fun_;
			} conn_;

	};
}

#endif
