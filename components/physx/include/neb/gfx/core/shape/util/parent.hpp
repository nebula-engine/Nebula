#ifndef NEBULA_GFX_CORE_SHAPE_UTIL_PARENT_HPP
#define NEBULA_GFX_CORE_SHAPE_UTIL_PARENT_HPP

#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <gal/itf/shared.hpp>

#include <neb/core/interface/Pose.hh>
#include <neb/core/util/parent.hpp>
#include <neb/core/core/actor/util/decl.hpp>
#include <neb/core/core/actor/util/cast.hpp>
#include <neb/core/core/shape/util/cast.hpp>

namespace neb {
	namespace gfx {
		namespace core {
			namespace shape {
				namespace util {
					/** @brief @parent
					 * abstract class for parent of a shape
					 *
					 * @note inheritance of neb::util::parent is non-virtual
					 */
					class parent :
						virtual public neb::core::core::shape::util::parent
					{
					public:
						virtual ~parent() {}
					};


				}
			}
		}
	}
}


#endif






