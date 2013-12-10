#ifndef __NEBULA_UI_OBJECT_TEXTVIEW_HPP__
#define __NEBULA_UI_OBJECT_TEXTVIEW_HPP__

#include <glutpp/gui/object/object.h>

namespace glutpp
{
	namespace gui
	{
		namespace object
		{
			/** \brief %textview
			 * Display and optionally edit text
			 */
			class textview:
				public glutpp::gui::object::object
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
					virtual int				handle_key(unsigned short,int);
					virtual int				handle_key_down(unsigned short);
					/** \brief key up
					*/
					virtual int				handle_key_up(unsigned short);
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
}

#endif

