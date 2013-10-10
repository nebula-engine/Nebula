#ifndef __NEBULA_UI_OBJECT_BASE_HPP__
#define __NEBULA_UI_OBJECT_BASE_HPP__

#include <jess/shared_ptr.hpp>

#include <nebula/define.hpp>

#include <nebula/ns.hpp>

namespace nebula
{
	namespace ui
	{
		namespace object
		{
			class base
			{
			public:
				virtual void		render( jess::shared_ptr<npr::base> ) = 0;
				
				UINT			x_;
				UINT			y_;
				UINT			w_;
				UINT			h_;
			};
		}
	}
}


#endif

