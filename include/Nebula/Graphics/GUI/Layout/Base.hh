#ifndef __NEBULA_UI_LAYOUT_BASE_HPP__
#define __NEBULA_UI_LAYOUT_BASE_HPP__

#include <map>

//#include <PxPhysicsAPI.h>

#include <Nebula/Graphics/GUI/Object/Base.hh>
#include <Nebula/Graphics/GUI/Layout/Util/Parent.hh>
#include <Nebula/Graphics/GUI/Object/Util/Parent.hh>
#include <Nebula/Graphics/Drawable/Base.hpp>

#include <Nebula/Graphics/Window/Base.hh>
#include <Nebula/Util/typedef.hpp>

namespace neb {
	namespace Graphics {
		namespace GUI {
			namespace Layout {
			/** @brief %Base */
				class Base:
					virtual public neb::std::shared,
					virtual public Neb::Graphics::Drawable::Base,
					virtual public Neb::Graphics::GUI::Object::Util::Parent
				{
					public:
						Base();
						Base(Neb::Graphics::GUI::Layout::Util::Parent_s parent);

						virtual void				init();


						/** @brief Main Loop @{ */
						virtual void					step(Neb::Core::TimeStep const & ts);
						virtual void					draw(sp::shared_ptr<Neb::Graphics::Context::Base> context);
						/** @} */

						void						connect(
								sp::shared_ptr<Neb::Graphics::Window::Base> const & window);
						int						search(
								sp::shared_ptr<Neb::Graphics::Window::Base> const & ,int button, int action, int mods);
						int						mouse_button_fun(
								sp::shared_ptr<Neb::Graphics::Window::Base> const & ,int button, int action, int mods);
						int						key_fun(
								sp::shared_ptr<Neb::Graphics::Window::Base> const & ,int,int,int,int);
					public:
						glm::mat4x4					ortho_;


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



