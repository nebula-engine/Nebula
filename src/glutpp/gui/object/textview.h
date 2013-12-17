#ifndef __NEBULA_UI_OBJECT_TEXTVIEW_HPP__
#define __NEBULA_UI_OBJECT_TEXTVIEW_HPP__

#include <glutpp/gui/object/object.h>

namespace glutpp
{
	namespace gui
	{
		namespace object
		{
			/** \brief %textview
			 * Display and optionally edit text
			 */
			class textview:
				public glutpp::gui::object::object
			{
				public:
					textview();
					void					clear_label();
					virtual void				draw();

					int					key(int key, int scancode, int action, int mods);
					int					key_down(int);
					virtual int				enter();

					size_t					label_pos_;

					virtual int				key_fun(int,int,int,int);
					virtual int				mouse_button_fun(int,int,int);

					virtual void				connect();

			};
		}
	}
}

#endif

