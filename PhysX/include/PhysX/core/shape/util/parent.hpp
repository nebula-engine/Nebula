#ifndef PHYSX_CORE_SHAPE_PARENT_HPP
#define PHYSX_CORE_SHAPE_PARENT_HPP

#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

//#include <galaxy/flag.hpp>
/*
#include <math/vec4.hpp>
#include <math/vec3.hpp>
#include <math/vec2.hpp>
#include <math/transform.hpp>
#include <math/geo/polyhedron.hpp>
*/
#include <neb/config.hh> // Nebula/config.hpp.in

#include <neb/core/shape/Util/Parent.hh>

#include <neb/core/Pose.hh>

#include <PhysX/core/actor/util/cast.hpp>
#include <PhysX/core/shape/util/cast.hpp>

namespace phx { namespace core { namespace shape { namespace util {



			/** @brief @Parent
			 * abstract class for parent of a shape
			 */
			class parent:
				virtual public neb::core::shape::util::parent,
				virtual public phx::core::actor::util::cast,
				virtual public phx::core::shape::util::cast
			{
				public:
					virtual ~parent() {}
			};
		

	
}}}}

#endif





