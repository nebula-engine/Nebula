#ifndef __NEBULA_UI_OBJECT_TEXTVIEW_HPP__
#define __NEBULA_UI_OBJECT_TEXTVIEW_HPP__

#include <nebula/ns.hpp>

#include <nebula/ui/object/base.hpp>

namespace nebula
{
	namespace ui
	{
		namespace object
		{
			/// %textview
			/**
			 * Display and optionally edit text
			 */
			class textview:
				public n52000::base
			{
				public:
					/** \brief render
					*/			
					virtual void				render( jess::shared_ptr<n23000::base> rnd );
					/** \brief key down
					*/
					virtual bool				key_down( int );
					/** \brief key up
					*/
					virtual bool				key_up( int );

			};
		}
	}
}

#endif

