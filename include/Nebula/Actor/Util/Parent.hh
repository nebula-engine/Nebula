#ifndef __GRU_ACTOR_PARENT_H__
#define __GRU_ACTOR_PARENT_H__

#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Nebula/Util/Shared.hh>
#include <Nebula/Util/Parent.hh>


#include <Nebula/Scene/Util/Cast.hh>

#include <Nebula/Actor/Util/Types.hh>
#include <Nebula/Actor/Util/Cast.hh>

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
				virtual public Neb::Util::Parent<Neb::Actor::Base>,
				virtual public Neb::Core::Pose,
				virtual public Neb::Scene::Util::Cast,
				virtual public Neb::Actor::Util::Cast,
				virtual public Neb::Util::Shared
			{
				public:
					Parent();
					virtual ~Parent() {}

					Neb::Scene::Base_s			getScene();
			};
		}
	}
}

#endif

