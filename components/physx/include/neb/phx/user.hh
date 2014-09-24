#ifndef __NEBULA_USER_H__
#define __NEBULA_USER_H__

//#include <gru/master.hpp>
#include <neb/gfx/window/Base.hh>

//#include <nebula/config.hpp>
//#include <nebula/camera/camera.hpp>

#include <neb/core/core/actor/util/decl.hpp>

namespace neb { namespace phx {
	class user {
		public:
			user();
			void	init();
			void	connect(std::shared_ptr<neb::gfx::window::base>);
			void	set_control(std::shared_ptr<phx::core::actor::control::rigidbody::base>);
			
			
			std::shared_ptr<phx::core::actor::control::rigidbody::base>		control_;
			
	};
}}

#endif
