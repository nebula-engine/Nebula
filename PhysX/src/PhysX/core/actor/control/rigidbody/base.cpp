

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <PxPhysicsAPI.h>

#include <Galaxy-Log/log.hpp>

#include <PhysX/core/actor/rigidbody/base.hpp>
#include <PhysX/core/actor/control/rigidbody/base.hpp>
#include <PhysX/util/convert.hpp>

phx::core::actor::control::rigidbody::base::base() {

}
void			phx::core::actor::control::rigidbody::base::serialize(boost::archive::polymorphic_iarchive & ar, unsigned int const & version) {
	abort();
}
void			phx::core::actor::control::rigidbody::base::serialize(boost::archive::polymorphic_oarchive & ar, unsigned int const & version) {
	abort();
}
int			phx::core::actor::control::rigidbody::base::key_fun(sp::shared_ptr<neb::gfx::window::base> window, int key, int scancode, int action, int mods) {
	//NEBULA_DEBUG_0_FUNCTION;

	BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;

/*	long unsigned int f = flag_.val_ & (
			neb::gfx::camera::view::util::flag::NORTH |
			neb::gfx::camera::view::util::flag::SOUTH |
			neb::gfx::camera::view::util::flag::EAST |
			neb::gfx::camera::view::util::flag::WEST |
			neb::gfx::camera::view::util::flag::UP |
			neb::gfx::camera::view::util::flag::DOWN);*/


	BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug)
		<< "key = " << key
		<< " scancode = " << scancode
		<< " action = " << action
		<< " mods = " << mods
		<< " flag = ";

	vec4 x(1.0,0.0,0.0,0);
	vec4 y(0.0,1.0,0.0,0);
	vec4 z(0.0,0.0,1.0,0);

	switch(action) {
		case GLFW_PRESS:
			switch(key) {
				case GLFW_KEY_D:
					f_ += x;
					return 1;
				case GLFW_KEY_A:
					f_ -= x;
					return 1;
				case GLFW_KEY_E:
					f_ += y;
					return 1;
				case GLFW_KEY_Q:
					f_ -= y;
					return 1;
				case GLFW_KEY_W:
					f_ -= z;
					return 1;
				case GLFW_KEY_S:
					f_ += z;
					return 1;
				case GLFW_KEY_I:
					t_ += x;
					return 1;
				case GLFW_KEY_K:
					t_ -= x;
					return 1;
				case GLFW_KEY_L:
					t_ -= y;
					return 1;
				case GLFW_KEY_J:
					t_ += y;
					return 1;
				case GLFW_KEY_O:
					t_ -= z;
					return 1;
				case GLFW_KEY_U:
					t_ += z;
					return 1;
				default:
					return 0;
			}
		case GLFW_RELEASE:
			switch(key) {
				case GLFW_KEY_D:
					f_ -= x;
					return 1;
				case GLFW_KEY_A:
					f_ += x;
					return 1;
				case GLFW_KEY_E:
					f_ -= y;
					return 1;
				case GLFW_KEY_Q:
					f_ += y;
					return 1;
				case GLFW_KEY_W:
					f_ += z;
					return 1;
				case GLFW_KEY_S:
					f_ -= z;
					return 1;
				case GLFW_KEY_I:
					t_ -= x;
					return 1;
				case GLFW_KEY_K:
					t_ += x;
					return 1;
				case GLFW_KEY_L:
					t_ += y;
					return 1;
				case GLFW_KEY_J:
					t_ -= y;
					return 1;
				case GLFW_KEY_O:
					t_ += z;
					return 1;
				case GLFW_KEY_U:
					t_ -= z;
					return 1;
				default:
					return 0;
			}
	}


	return 0;
}



