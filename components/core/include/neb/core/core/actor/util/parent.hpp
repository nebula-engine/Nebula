#ifndef __GRU_ACTOR_PARENT_H__
#define __GRU_ACTOR_PARENT_H__

#include <map>

#include <gal/itf/shared.hpp>

#include <neb/core/util/parent.hpp>

#include <neb/core/core/actor/__base.hpp>
#include <neb/core/core/actor/util/decl.hpp>
#include <neb/core/core/actor/util/cast.hpp>
#include <neb/core/core/scene/util/cast.hpp>
#include <neb/core/core/scene/util/decl.hpp>
#include <neb/core/interface/Pose.hh>

namespace neb { namespace core { namespace core { namespace actor { namespace util {
	/** @brief %arent
	 * abstract class for parent of an %actor
	 */
	class parent:
		virtual public neb::util::parent<neb::core::core::actor::__base, parent>,
		virtual public neb::core::core::scene::util::cast,
		virtual public neb::core::core::actor::util::cast,
		virtual public neb::core::Pose
	{
		public:
			parent();
			virtual ~parent();

		public:
			//shared_ptr<neb::core::core::scene::base>			getScene();
	};
}}}}}

#endif

