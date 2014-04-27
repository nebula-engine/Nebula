#ifndef __GLUTPP_PARENT_H__
#define __GLUTPP_PARENT_H__

#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <galaxy/flag.hpp>

#include <math/vec4.hpp>
#include <math/vec3.hpp>
#include <math/vec2.hpp>
#include <math/transform.hpp>
#include <math/geo/polyhedron.hpp>

#include <gru/config.hpp>
#include <gru/shared.hpp>
#include <gru/shape/desc.hpp>
#include <gru/material.hpp>
#include <gru/mesh.hpp>

namespace glutpp {
	namespace shape {
		/** @brief @Parent
		 * abstract class for parent of a shape
		 */
		class parent: virtual public gru::shared {
			public:
				virtual ~parent() {}

				virtual math::mat44<float>		getPoseGlobal() = 0;
				virtual math::mat44<float>		getPose() = 0;

				glutpp::actor::actor_s			isActor();
				glutpp::shape::shape_s			isShape();
		};
	}
}

#endif





