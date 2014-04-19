#ifndef __NEBULA_UI_OBJECT_EDITTEXT_H__
#define __NEBULA_UI_OBJECT_EDITTEXT_H__

#include <gru/gui/object/textview.hpp>

namespace glutpp {
	namespace gui {
		namespace object {
			class edittext: public glutpp::gui::object::textview {
				public:
					edittext();
					virtual void		draw();
					virtual void		connect();


					virtual int		key_fun(int,int,int,int);
					virtual int		mouse_button_fun(int,int,int);
					
					
					virtual int		enter();
			};
		}
	}
}

#endif

