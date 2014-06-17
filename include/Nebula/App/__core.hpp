#ifndef __NEBULA_APP___CORE_H__
#define __NEBULA_APP___CORE_H__

#include <Nebula/App/__base.hpp>
#include <Nebula/Scene/Util/Parent.hh>
#include <Nebula/Graphics/GUI/Layout/Util/Parent.hh>

namespace neb {
	namespace app {
		class __core:
			virtual public neb::app::__base,
			virtual public neb::gfx::gui::layout::util::parent,
			virtual public neb::scene::util::parent
		{
			public:
				virtual void	init();

		};
	}
}

#endif





