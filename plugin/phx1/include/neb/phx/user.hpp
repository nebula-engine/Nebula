#ifndef __NEBULA_USER_H__
#define __NEBULA_USER_H__

//#include <gru/master.hpp>
//#include <neb/gfx/window/Base.hh>

//#include <nebula/config.hpp>
//#include <nebula/camera/camera.hpp>

#include <neb/fnd/input/util/decl.hpp>
#include <neb/fnd/core/actor/util/decl.hpp>

#include <neb/fnd/core/actor/util/decl.hpp>

namespace neb { namespace phx {
	/** @brief
	 *
	 */
	class user
	{
		public:
			user();
			void		init();
			void		connect(std::shared_ptr<neb::fnd::input::source>);
			void		set_control(std::shared_ptr<neb::fnd::core::actor::control::rigidbody::base>);
			std::shared_ptr<neb::fnd::core::actor::control::rigidbody::base>		control_;
			
	};
}}

#endif
