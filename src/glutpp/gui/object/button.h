#ifndef __NEBULA_UI_OBJECT_BUTTON_HPP__
#define __NEBULA_UI_OBJECT_BUTTON_HPP__

#include <glutpp/gui/object/object.h>

namespace glutpp
{
	namespace gui
	{
		namespace object
		{
			class button:
				public glutpp::gui::object::object
			{
				public:
					virtual void		draw();

					virtual int				key_fun(int,int,int,int);
					virtual int				mouse_button_fun(int,int,int);

					virtual void				connect();

			};
		}
	}
}

#endif



