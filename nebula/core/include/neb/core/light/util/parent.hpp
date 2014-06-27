#ifndef NEBULA_CORE_LIGHT_UTIL_PARENT_HH
#define NEBULA_CORE_LIGHT_UTIL_PARENT_HH

#include <neb/core/Pose.hh>
#include <neb/core/shape/util/Cast.hh>
#include <neb/core/light/__base.hpp>
#include <neb/util/parent.hpp>

namespace neb { namespace core { namespace light { namespace util {



	class parent:
		virtual public neb::util::parent<neb::core::light::__base>,
		virtual public neb::core::shape::util::cast,
		virtual public neb::core::Pose
	{
		public:
			virtual ~parent() {}
	};



}}}}

#endif
