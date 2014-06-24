#ifndef __NEBULA_APP___CORE_H__
#define __NEBULA_APP___CORE_H__

#include <Nebula/app/__base.hpp>
#include <Nebula/core/scene/Util/Parent.hh>
#include <Nebula/gfx/GUI/Layout/Util/Parent.hh>

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





