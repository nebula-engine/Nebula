#ifndef __NEBULA_APP_H__
#define __NEBULA_APP_H__

#include <Nebula/Scene/Util/Parent.hh>
#include <Nebula/Graphics/GUI/Layout/Util/Parent.hh>

namespace Neb {
	namespace App {
		class __core:
			virtual public Neb::App::__base,
			virtual public Neb::Graphics::GUI::Layout::Util::Parent,
			virtual public Neb::Scene::Util::Parent
		{


		};
	}
}

#endif





