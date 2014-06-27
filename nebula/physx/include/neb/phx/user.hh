#ifndef __NEBULA_USER_H__
#define __NEBULA_USER_H__

//#include <gru/master.hpp>
#include <neb/gfx/window/Base.hh>

//#include <nebula/config.hpp>
//#include <nebula/camera/camera.hpp>

#include <neb/core/actor/Util/Types.hh>

namespace phx {
	class user {
		public:
			user();
			void	init();
			void	connect(sp::shared_ptr<neb::gfx::window::base>);
			void	set_control(sp::shared_ptr<phx::core::actor::control::rigidbody::base>);
			
			
			sp::shared_ptr<phx::core::actor::control::rigidbody::base>		control_;
			
	};
}

#endif
