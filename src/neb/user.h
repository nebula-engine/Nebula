#ifndef __NEBULA_USER_H__
#define __NEBULA_USER_H__

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

			std::shared_ptr<neb::actor::Base>		actor_;
			
			std::shared_ptr<glutpp::camera_control>		camera_control_;
			
	};
}

#endif
