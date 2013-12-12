#ifndef __NEBULA_UI_OBJECT_BUTTON_HPP__
#define __NEBULA_UI_OBJECT_BUTTON_HPP__

#include <glutpp/gui/object/object.h>

namespace GUL
{
	namespace object
	{
		class button:
			public glutpp::gui::object::object
		{
			public:
				virtual void		Display();
		};
	}
}

#endif



