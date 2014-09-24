

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

void		neb::phx::core::actor::control::rigidbody::manual::step(gal::etc::timestep const & ts) { // 0

}

vec3			neb::phx::core::actor::control::rigidbody::manual::f_body() {
	LOG(lg, neb::phx::core::actor::sl, debug) << __PRETTY_FUNCTION__;
	return f_ * 10.0f;
}
vec3			neb::phx::core::actor::control::rigidbody::manual::t_body() {
	LOG(lg, neb::phx::core::actor::sl, debug) << __PRETTY_FUNCTION__;
	return t_ * 3.0f;
}
vec3			neb::phx::core::actor::control::rigidbody::manual::f_global() {
	LOG(lg, neb::phx::core::actor::sl, debug) << __PRETTY_FUNCTION__;
	return vec3();
}
vec3			neb::phx::core::actor::control::rigidbody::manual::t_global() {
	LOG(lg, neb::phx::core::actor::sl, debug) << __PRETTY_FUNCTION__;
	return vec3();
}



