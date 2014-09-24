#ifndef __GLUTPP_PARENT_H__
#define __GLUTPP_PARENT_H__

#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <gal/itf/shared.hpp>

#include <neb/core/interface/Pose.hh>
#include <neb/core/core/actor/util/decl.hpp>
#include <neb/core/core/actor/util/cast.hpp>
#include <neb/core/core/shape/util/cast.hpp>
#include <neb/core/util/parent.hpp>

namespace neb { namespace core { namespace core { namespace shape { namespace util {
	/** @brief %parent
	 * abstract class for parent of a shape
	 *
	 * @note inheritance of neb::util::parent is non-virtual
	 */
	class parent:
		virtual public neb::util::parent<neb::core::core::shape::base>,
		virtual public neb::core::core::actor::util::cast,
		virtual public neb::core::core::shape::util::cast,
		virtual public neb::core::Pose
	{
		public:
			virtual ~parent() {}
			void		callbackPose(neb::core::pose const & pose);
	};
}}}}}

#endif

