#ifndef __GRU_ACTOR_PARENT_H__
#define __GRU_ACTOR_PARENT_H__

#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Galaxy-Standard/shared.hpp>

#include <Nebula/Util/parent.hpp>

#include <Nebula/Scene/Util/Cast.hh>

#include <Nebula/Actor/__base.hpp>
#include <Nebula/Actor/Util/Types.hh>
#include <Nebula/Actor/Util/Cast.hh>

#include <Nebula/Graphics/material.hh>
#include <Nebula/Graphics/mesh.hh>

#include <Nebula/Core/Pose.hh>

namespace neb {
	namespace Actor {
		namespace Util {
			/** @brief @Parent
			 * abstract class for parent of an @Actor
			 */
			class Parent:
				public neb::Util::parent<neb::actor::__base>,
				virtual public neb::core::Pose,
				virtual public neb::Scene::Util::Cast,
				virtual public neb::Actor::Util::Cast
			{
				public:
					Parent();
					virtual ~Parent() {}

					virtual void				init();
				public:
					neb::Scene::Base_s			getScene();
			};
		}
	}
}

#endif

