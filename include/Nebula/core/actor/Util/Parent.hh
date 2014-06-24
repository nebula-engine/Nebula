#ifndef __GRU_ACTOR_PARENT_H__
#define __GRU_ACTOR_PARENT_H__

#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Galaxy-Standard/shared.hpp>

#include <Nebula/util/parent.hpp>

#include <Nebula/core/scene/Util/Cast.hh>

#include <Nebula/core/actor/__base.hpp>
#include <Nebula/core/actor/Util/Types.hh>
#include <Nebula/core/actor/Util/Cast.hh>

#include <Nebula/gfx/material.hh>
#include <Nebula/gfx/mesh.hh>

#include <Nebula/core/Pose.hh>

namespace neb { namespace core { namespace actor { namespace util {


	/** @brief @Parent
	 * abstract class for parent of an @Actor
	 */
	class parent:
		virtual public neb::util::parent<neb::actor::__base>,
		virtual public neb::core::Pose,
		virtual public neb::core::scene::util::cast,
		virtual public neb::core::actor::util::cast
	{
		public:
			parent();
			virtual ~parent();

			virtual void						init();
		public:
			sp::shared_ptr<neb::core::scene::base>			getScene();
	};



}}}}

#endif

