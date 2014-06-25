#ifndef __NEBULA_APP___CORE_H__
#define __NEBULA_APP___CORE_H__

#include <neb/app/__base.hpp>
#include <neb/core/scene/Util/Parent.hh>
#include <neb/gfx/GUI/Layout/Util/Parent.hh>

namespace neb {
	namespace app {
		class __core:
			virtual public neb::app::__base,
			virtual public neb::gfx::gui::layout::util::parent,
			virtual public neb::core::scene::util::parent
		{
			public:
				virtual void	init();
				virtual void	release() {}

		};
	}
}

#endif





