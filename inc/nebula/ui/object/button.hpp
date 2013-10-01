#ifndef __NEBULA_UI_OBJECT_BUTTON_HPP__
#define __NEBULA_UI_OBJECT_BUTTON_HPP__

#include <nebula/utilities/types/platform/types.hpp>

#include <nebula/ui/object/base.hpp>

#include <nebula/ns.hpp>

namespace nebula
{
	namespace ui
	{
		namespace object
		{
			class button:
				public nuo::base
			{
			public:
				virtual void		render( const boost::shared_ptr<npr::base>& );
			};
		}
	}
}

#endif



