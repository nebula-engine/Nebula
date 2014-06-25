#ifndef __NEBULA_UI_LAYOUT_BASE_HPP__
#define __NEBULA_UI_LAYOUT_BASE_HPP__

#include <map>

#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/GUI/Object/Base.hh>
//#include <neb/gfx/GUI/Layout/Util/Parent.hh>
#include <neb/gfx/GUI/Object/Util/Parent.hh>
#include <neb/gfx/Drawable/Base.hpp>

#include <neb/gfx/window/Base.hh>
#include <neb/util/typedef.hpp>

namespace neb {
	namespace gfx {
		namespace gui {
			namespace layout {
			/** @brief %Base */
				class base:
					virtual public neb::std::shared,
					virtual public neb::gfx::drawable::base,
					virtual public neb::gfx::gui::object::util::parent
				{
					public:
						//base();
						base(sp::shared_ptr<neb::gfx::gui::layout::util::parent> parent);

						virtual void				init();
						virtual void				release() {}


						/** @brief Main Loop @{ */
						virtual void					step(gal::std::timestep const & ts);
						virtual void					draw(sp::shared_ptr<neb::gfx::context::base> context, sp::shared_ptr<neb::glsl::program> p);
						/** @} */

						void						connect(
								sp::shared_ptr<neb::gfx::window::base> const & window);
						int						search(
								sp::shared_ptr<neb::gfx::window::base> const & ,int button, int action, int mods);
						int						mouse_button_fun(
								sp::shared_ptr<neb::gfx::window::base> const & ,int button, int action, int mods);
						int						key_fun(
								sp::shared_ptr<neb::gfx::window::base> const & ,int,int,int,int);
					public:
						glm::mat4x4					ortho_;


						sp::shared_ptr<neb::gfx::gui::layout::util::parent>	parent_;
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



