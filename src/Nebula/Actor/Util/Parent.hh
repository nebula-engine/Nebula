#ifndef __GRU_ACTOR_PARENT_H__
#define __GRU_ACTOR_PARENT_H__

#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Nebula/config.hh>
#include <Nebula/Util/Shared.hh>

#include <Nebula/Scene/Util/Cast.hh>

#include <Nebula/Actor/Util/Types.hh>
#include <Nebula/Actor/Util/Address.hh>
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
				virtual public Neb::Core::Pose,
				virtual public Neb::Scene::Util::Cast,
				virtual public Neb::Actor::Util::Cast,
				virtual public Neb::Util::Shared
			{
				public:
					Parent();
					virtual ~Parent() {}

					//virtual physx::PxMat44		getPoseGlobal() = 0;
					//virtual physx::PxMat44		getPose() = 0;
					void					insertActor(Neb::Actor::Base_s actor);
					void					insertActor(Neb::Actor::Base_s actor, int i);

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

