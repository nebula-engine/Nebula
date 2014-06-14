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
			void	connect(sp::shared_ptr<neb::gfx::window::base>);
			void	set_control(sp::shared_ptr<neb::core::actor::Control::RigidBody::base>);
			
			
			sp::shared_ptr<neb::core::actor::Control::RigidBody::base>		control_;
			
	};
}

#endif
