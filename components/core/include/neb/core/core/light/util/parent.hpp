#ifndef NEBULA_CORE_LIGHT_UTIL_PARENT_HH
#define NEBULA_CORE_LIGHT_UTIL_PARENT_HH

#include <neb/core/interface/Pose.hh>
#include <neb/core/util/parent.hpp>
#include <neb/core/core/scene/util/decl.hpp>
#include <neb/core/core/shape/util/cast.hpp>
#include <neb/core/core/light/__base.hpp>

namespace neb { namespace core { namespace core { namespace light { namespace util {
	class parent:
		virtual public neb::util::parent<neb::core::light::__base, parent>,
		virtual public neb::core::core::shape::util::cast,
		virtual public neb::core::Pose
	{
		public:
			virtual ~parent() {}
			//bool							hasScene();
			//std::weak_ptr<neb::core::core::scene::base>		getScene();

			void							callbackPose(neb::core::pose const &);
	};
}}}}}

#endif
