#ifndef __GRU_ACTOR_PARENT_H__
#define __GRU_ACTOR_PARENT_H__

#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Galaxy-Standard/shared.hpp>

#include <neb/util/parent.hpp>

#include <neb/core/scene/Util/Cast.hh>

#include <neb/core/actor/__base.hpp>
#include <neb/core/actor/Util/Types.hh>
#include <neb/core/actor/Util/Cast.hh>

//#include <neb/gfx/material.hh>
//#include <neb/gfx/mesh.hh>

#include <neb/core/Pose.hh>

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
			virtual void						release();
		public:
			sp::shared_ptr<neb::core::scene::base>			getScene();
	};



}}}}

#endif

