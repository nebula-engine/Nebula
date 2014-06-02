#ifndef __NEBULA_UI_LAYOUT_BASE_HPP__
#define __NEBULA_UI_LAYOUT_BASE_HPP__

#include <map>

#include <PxPhysicsAPI.h>

#include <Nebula/Graphics/GUI/Object/Base.hh>
#include <Nebula/Graphics/GUI/Layout/Util/Parent.hh>
#include <Nebula/Graphics/GUI/Object/Util/Parent.hh>

#include <Nebula/Graphics/Window/Base.hh>

namespace Neb {
	namespace Graphics {
		namespace GUI {
			namespace Layout {
			/** @brief %Base */
				class Base: virtual public Neb::Graphics::GUI::Object::Util::Parent {
					public:
						Base();
						Base(Neb::Graphics::GUI::Layout::Util::Parent_s parent);

						virtual void				init();

						Neb::Graphics::GUI::Layout::Util::Parent_s		getParent();

						/** @brief Main Loop @{ */
						void						render(double time);
						void						draw();
						/** @} */

						void						connect();

						int						search(int button, int action, int mods);

						int						mouse_button_fun(int button, int action, int mods);
						int						key_fun(int,int,int,int);
					public:
						physx::PxMat44					ortho_;


						Neb::Graphics::GUI::Layout::Util::Parent_s	parent_;
						// connections
						struct
						{
							boost::signals2::connection		mouse_button_fun_;
							boost::signals2::connection		key_fun_;
						} conns_;


				};
			}
		}
	}
}

#endif



