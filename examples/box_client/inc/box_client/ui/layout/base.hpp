#ifndef __BOX_CLIENT_UI_LAYOUT_BASE_HPP__
#define __BOX_CLIENT_UI_LAYOUT_BASE_HPP__

#include <nebula/ui/layout/base.hpp>

#include <box_client/ns.hpp>

namespace box_client
{
	namespace ui
	{
		namespace layout
		{
			class base:
				public nu::layout::base
			{
				virtual void		init();
			};
		}
	}
}

#endif
