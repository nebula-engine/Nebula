#ifndef __GLUTPP_PARENT_H__
#define __GLUTPP_PARENT_H__

#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <gal/flag.h>

#include <math/vec4.h>
#include <math/vec3.h>
#include <math/vec2.h>
#include <math/transform.h>
#include <math/geo/polyhedron.h>

#include <glutpp/config.h>
#include <glutpp/shape/desc.h>
#include <glutpp/material.h>
#include <glutpp/mesh.h>

namespace glutpp
{
	class parent: public std::enable_shared_from_this<parent>
	{
		public:
			parent(glutpp::parent_s = glutpp::parent_s());
			virtual ~parent();
			
			glutpp::parent_s		get_parent();
			
			math::mat44			get_pose_global();
			virtual math::mat44		get_pose() = 0;
			
			glutpp::parent_w		parent_;
	};
}

#endif





