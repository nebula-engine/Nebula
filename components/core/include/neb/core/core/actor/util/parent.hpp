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
<<<<<<< HEAD
		virtual public neb::util::parent<neb::actor::__base>,
=======
		virtual public neb::util::parent<neb::core::core::actor::__base, parent>,
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
		virtual public neb::core::core::scene::util::cast,
		virtual public neb::core::core::actor::util::cast,
		virtual public neb::core::Pose
	{
		public:
			parent();
			virtual ~parent();

<<<<<<< HEAD
			virtual void						init();
			virtual void						release();
		public:
			shared_ptr<neb::core::core::scene::base>			getScene();
=======
		public:
			//shared_ptr<neb::core::core::scene::base>			getScene();
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
	};
}}}}}

#endif

