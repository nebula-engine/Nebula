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
#include <gru/shape/desc.hpp>
#include <gru/material.hpp>
#include <gru/mesh.hpp>

namespace glutpp {
	/** @brief @Parent
	 * abstract class for parent of a shape
	 * actor and shape derive from this
	 */
	class parent: public std::enable_shared_from_this<parent> {
		public:
			parent(glutpp::parent_s = glutpp::parent_s());
			virtual ~parent();
			
			glutpp::parent_s		get_parent();
			
			math::mat44			get_pose_global();
			virtual math::mat44		get_pose() = 0;
			
			glutpp::parent_w		parent_;
			
			glutpp::actor::actor_s		is_actor();
			glutpp::shape::shape_s		is_shape();
	};
}

#endif





