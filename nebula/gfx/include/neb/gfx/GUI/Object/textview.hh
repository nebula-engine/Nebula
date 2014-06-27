#ifndef __NEBULA_UI_OBJECT_TEXTVIEW_HPP__
#define __NEBULA_UI_OBJECT_TEXTVIEW_HPP__

#include <neb/gfx/GUI/Object/Base.hh>

namespace neb {
	namespace gfx {
		namespace gui {
			namespace object {
				/** \brief %textview
				 * Display and optionally edit text
				 */
				class textview:
					public neb::gfx::gui::object::base
				{
					public:
						textview();
						void			clear_label();
						virtual void		draw(sp::shared_ptr<neb::glsl::program> p);

						//int			key(int, int, int, int);
						//int			key_down(int);
						//virtual int		enter();

						virtual int		key_fun(sp::shared_ptr<neb::gfx::window::base> const & window, int,int,int,int);
						virtual int		mouse_button_fun(sp::shared_ptr<neb::gfx::window::base> const & window, int,int,int);
						//virtual void		connect();

				};
			}
		}
	}
}

#endif

