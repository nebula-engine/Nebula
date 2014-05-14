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

#include <Nebula/config.hh>
#include <Nebula/Util/Shared.hh>

#include <Nebula/Graphics/material.hh>
#include <Nebula/Graphics/mesh.hh>

#include <Nebula/Core/Pose.hh>

namespace Neb {
	namespace Actor {
		namespace Util {
			/** @brief @Parent
			 * abstract class for parent of an @Actor
			 */
			class Parent:
				virtual public Neb::Core::Pose,
				virtual public Neb::Util::Shared
			{
				public:
					Parent();
					virtual ~Parent() {}

					//virtual physx::PxMat44					getPoseGlobal() = 0;
					//virtual physx::PxMat44					getPose() = 0;

					Neb::Actor::Base_s			getActor(Neb::Actor::Util::index_type i);
					Neb::Actor::Base_s			getActor(Neb::Actor::Util::Address address);

					void					releaseActor(Neb::Actor::Util::index_type i);

					Neb::Actor::Base_s			isActor();
					Neb::Scene::Base_s			isScene();

					Neb::Scene::Base_s			getScene();

				protected:
					Neb::Map<Neb::Actor::Base>		actors_;
			};
		}
	}
}

#endif





