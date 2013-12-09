#ifndef __NEBULA_UI_OBJECT_EDITTEXT_H__
#define __NEBULA_UI_OBJECT_EDITTEXT_H__

#include <GUL/object/textview.h>

namespace GUL
{
	namespace object
	{
		class edittext:
			public GUL::object::textview
		{
			public:
				edittext();
				virtual void		Display();
		};
	}
}

#endif

