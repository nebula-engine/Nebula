#ifndef __GRU_ACTOR_PARENT_H__
#define __GRU_ACTOR_PARENT_H__

#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

/*
#include <galaxy/flag.hpp>

#include <math/vec4.hpp>
#include <math/vec3.hpp>
#include <math/vec2.hpp>
#include <math/transform.hpp>
#include <math/geo/polyhedron.hpp>
*/

#include <gru/config.hpp>
#include <gru/shared.hpp>
#include <gru/shape/desc.hpp>
#include <gru/Graphics/material.hpp>
#include <gru/Graphics/mesh.hpp>

namespace glutpp {
	namespace actor {
		/** @brief @Parent
		 * abstract class for parent of an @Actor
		 */
		class parent: virtual public gru::shared {
			public:
				virtual ~parent() {}

				virtual physx::PxMat44					getPoseGlobal() = 0;
				virtual physx::PxMat44					getPose() = 0;

				Neb::weak_ptr<glutpp::actor::actor>			isActor();
				Neb::weak_ptr<glutpp::scene::scene>			isScene();
				
				Neb::weak_ptr<glutpp::scene::scene>			getScene();
		};
	}
}

#endif





