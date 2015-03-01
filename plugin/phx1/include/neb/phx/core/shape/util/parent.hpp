#ifndef NEB_PHX_CORE_SHAPE_PARENT_HPP
#define NEB_PHX_CORE_SHAPE_PARENT_HPP

#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <neb/fnd/util/config.hpp>
#include <neb/fnd/core/shape/util/parent.hpp>
#include <neb/fnd/itf/Pose.hpp>

#include <neb/phx/core/actor/util/cast.hpp>
#include <neb/phx/core/shape/util/cast.hpp>

namespace neb { namespace phx { namespace core { namespace shape { namespace util {
	/** @brief @Parent
	 * abstract class for parent of a shape
	 */
	class parent:
		virtual public neb::fnd::core::shape::util::parent,
		virtual public neb::phx::core::actor::util::cast,
		virtual public neb::phx::core::shape::util::cast
	{
		public:
			virtual ~parent() {}
	};
}}}}}

#endif





