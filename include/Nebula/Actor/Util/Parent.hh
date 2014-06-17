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

namespace neb { namespace core {
	namespace actor {
		namespace util {
			/** @brief @Parent
			 * abstract class for parent of an @Actor
			 */
			class parent:
				public neb::util::parent<neb::actor::__base>,
				virtual public neb::core::Pose,
				virtual public neb::scene::util::cast,
				virtual public neb::core::actor::util::cast
			{
				public:
					parent();
					virtual ~parent() {}

					virtual void				init();
				public:
					sp::shared_ptr<neb::scene::base>			getScene();
			};
		}
	}
}}

#endif

