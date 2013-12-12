#ifndef __NEBULA_UI_OBJECT_EDITTEXT_H__
#define __NEBULA_UI_OBJECT_EDITTEXT_H__

#include <glutpp/gui/object/textview.h>

namespace glutpp
{
namespace gui
{
	namespace object
	{
		class edittext:
			public glutpp::gui::object::textview
		{
			public:
				edittext();
				virtual void		Display();
		};
	}
}
}

#endif

