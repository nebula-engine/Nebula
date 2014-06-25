#ifndef __NEBULA_UI_OBJECT_EDITTEXT_H__
#define __NEBULA_UI_OBJECT_EDITTEXT_H__

#include <neb/gfx/GUI/Object/textview.hh>

namespace neb {
	namespace gfx {
		namespace gui {
			namespace object {
				class edittext: public neb::gfx::gui::object::textview {
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
}

#endif



