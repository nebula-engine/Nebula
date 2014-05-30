#ifndef __NEBULA_UI_OBJECT_EDITTEXT_H__
#define __NEBULA_UI_OBJECT_EDITTEXT_H__

#include <Nebula/Graphics/GUI/Object/textview.hh>

namespace Neb {
	namespace Graphics {
		namespace GUI {
			namespace Object {
				class edittext: public Neb::Graphics::GUI::Object::textview {
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



