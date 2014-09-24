

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <PxPhysicsAPI.h>

#include <gal/log/log.hpp>

#include <neb/core/util/debug.hpp>

#include <neb/phx/core/actor/rigidbody/base.hpp>
#include <neb/phx/core/actor/control/rigidbody/base.hpp>
#include <neb/phx/util/convert.hpp>
#include <neb/phx/util/log.hpp>

neb::phx::core::actor::control::rigidbody::base::base() {

}
void			neb::phx::core::actor::control::rigidbody::base::serialize(boost::archive::polymorphic_iarchive & ar, unsigned int const & version) {
	abort();
}
void			neb::phx::core::actor::control::rigidbody::base::serialize(boost::archive::polymorphic_oarchive & ar, unsigned int const & version) {
	abort();
}
int			neb::phx::core::actor::control::rigidbody::base::key_fun(std::shared_ptr<neb::gfx::window::base> window, int key, int scancode, int action, int mods) {
	//NEBULA_DEBUG_0_FUNCTION;

	LOG(lg, neb::phx::core::actor::sl, debug) << __PRETTY_FUNCTION__;

/*	long unsigned int f = flag_.val_ & (
			neb::gfx::camera::view::util::flag::NORTH |
			neb::gfx::camera::view::util::flag::SOUTH |
			neb::gfx::camera::view::util::flag::EAST |
			neb::gfx::camera::view::util::flag::WEST |
			neb::gfx::camera::view::util::flag::UP |
			neb::gfx::camera::view::util::flag::DOWN);*/


	LOG(lg, neb::phx::core::actor::sl, debug)
		<< "key = " << key
		<< " scancode = " << scancode
		<< " action = " << action
		<< " mods = " << mods
		<< " flag = ";

	vec3 x(1.0,0.0,0.0);
	vec3 y(0.0,1.0,0.0);
	vec3 z(0.0,0.0,1.0);

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



