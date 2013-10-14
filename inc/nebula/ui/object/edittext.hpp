#ifndef __NEBULA_UI_OBJECT_TEXTVIEW_HPP__
#define __NEBULA_UI_OBJECT_TEXTVIEW_HPP__

#include <nebula/ns.hpp>
#include <nebula/ui/object/textview.hpp>

namespace nebula
{
	namespace ui
	{
		namespace object
		{
			/** \brief edittext
			 * Display and edit text
			 */
			class edittext:
				public n52000::textview
			{
				public:
					/// render
					virtual void						render( jess::shared_ptr<n23000::base> rnd );
			};
		}
	}
}

#endif

