#ifndef __NEBULA_UI_OBJECT_TEXTVIEW_HPP__
#define __NEBULA_UI_OBJECT_TEXTVIEW_HPP__

#include <glutpp/gui/object/object.h>

namespace GUL
{
	namespace object
	{
		/** \brief %textview
		 * Display and optionally edit text
		 */
		class textview:
			public GUL::object::object
		{
			public:
				/** \brief ctor
				 */
				textview();
				/** \brief clear label
				 */
				void					clear_label();
				/** \brief render
				 */			
				virtual void				Display();
				///@{
				/** on
				 */
				virtual int				handle_key(__u16, __s32);
				virtual int				handle_key_down(__u16);
				/** \brief key up
				 */
				virtual int				handle_key_up(__u16);
				/** \brief linefeed
				 */
				virtual int				handle_enter();
				///@}
				/** \brief linefeed
				 */
				std::function<int()>			callback_enter_;
				/** \brief label pos
				 */
				size_t					label_pos_;
		};
	}
}

#endif

