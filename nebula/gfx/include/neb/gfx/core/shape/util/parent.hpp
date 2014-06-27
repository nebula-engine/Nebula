#ifndef NEBULA_CORE_SHAPE_GFX_UTIL_PARENT_HPP
#define NEBULA_CORE_SHAPE_GFX_UTIL_PARENT_HPP

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
//#include <neb/config.hh> // Nebula/config.hpp.in

#include <neb/core/actor/util/Types.hh>
#include <neb/core/actor/util/Cast.hh>

//#include <neb/core/shape/util/Types.hh>
#include <neb/core/shape/util/Cast.hh>


#include <Galaxy-Standard/shared.hpp>

//#include <neb/gfx/material.hh>
//#include <neb/gfx/mesh.hh>

#include <neb/core/Pose.hh>
#include <neb/util/parent.hpp>

namespace neb { namespace core { namespace shape { namespace util {



			/** @brief @Parent
			 * abstract class for parent of a shape
			 *
			 * @note inheritance of neb::util::parent is non-virtual
			 */
			class parent:
				virtual public neb::util::parent<neb::core::shape::base>,
				virtual public neb::core::actor::util::cast,
				virtual public neb::core::shape::util::cast,
				virtual public neb::core::Pose
			{
				public:
					virtual ~parent() {}
			};


}}}}


#endif






