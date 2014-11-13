#ifndef __NEBULA_UI_OBJECT_TEXTVIEW_HPP__
#define __NEBULA_UI_OBJECT_TEXTVIEW_HPP__

#include <neb/gfx/gui/object/Base.hh>

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
						virtual void		draw(std::shared_ptr<neb::gfx::glsl::program::base> p);

						//int			key(int, int, int, int);
						//int			key_down(int);
						//virtual int		enter();

						virtual int		keyFun(std::shared_ptr<neb::core::input::source> const &, int,int,int,int);
						virtual int		mouseButtonFun(std::shared_ptr<neb::core::input::source> const &, int,int,int);
						//virtual void		connect();

				};
			}
		}
	}
}

#endif

