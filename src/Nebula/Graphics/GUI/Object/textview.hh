#ifndef __NEBULA_UI_OBJECT_TEXTVIEW_HPP__
#define __NEBULA_UI_OBJECT_TEXTVIEW_HPP__

#include <Nebula/Graphics/GUI/Object/object.hh>

namespace Neb {
	namespace gui {
		namespace object {
			/** \brief %textview
			 * Display and optionally edit text
			 */
			class textview:
				public Neb::gui::object::object
			{
				public:
					textview();
					void			clear_label();
					virtual void		draw();

					//int			key(int, int, int, int);
					//int			key_down(int);
					//virtual int		enter();

					virtual int		key_fun(int,int,int,int);
					virtual int		mouse_button_fun(int,int,int);
					//virtual void		connect();

			};
		}
	}
}

#endif

