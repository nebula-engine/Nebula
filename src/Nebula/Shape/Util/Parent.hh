#ifndef __GLUTPP_PARENT_H__
#define __GLUTPP_PARENT_H__

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
#include <Nebula/config.hh> // Nebula/config.hpp.in

#include <Nebula/Actor/Util/Types.hh>
#include <Nebula/Actor/Util/Cast.hh>

//#include <Nebula/Shape/Util/Types.hh>
#include <Nebula/Shape/Util/Cast.hh>


#include <Nebula/Util/Shared.hh>

#include <Nebula/Graphics/material.hh>
#include <Nebula/Graphics/mesh.hh>

#include <Nebula/Core/Pose.hh>

namespace Neb {
	namespace Shape {
		namespace Util {
			/** @brief @Parent
			 * abstract class for parent of a shape
			 */
			class Parent:
				virtual public Neb::Actor::Util::Cast,
				virtual public Neb::Shape::Util::Cast,
				virtual public Neb::Core::Pose,
				virtual public Neb::Util::Shared {
				public:
					Parent();
					virtual ~Parent() {}

					//virtual physx::PxMat44					getPoseGlobal() = 0;
					//virtual physx::PxMat44					getPose() = 0;

					/** @brief Shapes */
					Neb::Map<Neb::Shape::Base>		shapes_;

			};
		}
	}
}

#endif





