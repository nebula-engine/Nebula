

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <PxPhysicsAPI.h>

#include <Galaxy-Log/log.hpp>

#include <PhysX/core/actor/rigidbody/base.hpp>
#include <PhysX/core/actor/control/rigidbody/base.hpp>
#include <PhysX/util/convert.hpp>

void		phx::core::actor::control::rigidbody::manual::step(gal::std::timestep const & ts) { // 0

}

vec4			phx::core::actor::control::rigidbody::manual::f() {
	BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;
	return f_ * 30.0f;
}
vec4			phx::core::actor::control::rigidbody::manual::t() {
	BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;
	return t_ * 3.0f;
}




