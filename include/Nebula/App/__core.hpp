#ifndef __NEBULA_APP___CORE_H__
#define __NEBULA_APP___CORE_H__

#include <Nebula/App/__base.hpp>
#include <Nebula/Scene/Util/Parent.hh>
#include <Nebula/Graphics/GUI/Layout/Util/Parent.hh>

namespace neb {
	namespace App {
		class __core:
			virtual public neb::App::__base,
			virtual public neb::gfx::gui::layout::util::parent,
			virtual public neb::Scene::util::parent
		{
			public:
				virtual void	init();

		};
	}
}

#endif





