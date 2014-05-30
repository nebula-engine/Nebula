#ifndef __NEBULA_USER_H__
#define __NEBULA_USER_H__

//#include <gru/master.hpp>
#include <Nebula/Graphics/Window/Base.hh>

//#include <nebula/config.hpp>
//#include <nebula/camera/camera.hpp>

#include <Nebula/Actor/Util/Types.hh>

namespace Neb {
	class User {
		public:
			User();
			void	init();
			void	connect(Neb::Graphics::Window::Base_s);
			void	set_control(Neb::Actor::Control::RigidBody::Base_s);
			
			
			Neb::Actor::Control::RigidBody::Base_s		control_;
			
	};
}

#endif
