#ifndef __NEBULA_APP___CORE_H__
#define __NEBULA_APP___CORE_H__

#include <neb/core/app/__base.hpp>
#include <neb/core/core/scene/util/parent.hpp>

using namespace std;

namespace neb {
	namespace app {
		class __core:
			virtual public neb::core::app::__base,
			virtual public neb::core::core::scene::util::parent
		{
			protected:
				virtual void			__init();
			public:
				virtual void			release() {}
				static weak_ptr<neb::app::__core>	global();
				neb::core::pose			getPose();
				neb::core::pose			getPoseGlobal();
		};
	}
}

#endif





