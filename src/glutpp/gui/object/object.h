#ifndef __NEBULA_UI_OBJECT_BASE_HPP__
#define __NEBULA_UI_OBJECT_BASE_HPP__

#include <memory>

#include <gal/sig/connection.h>

#include <glutpp/master.h>

namespace glutpp
{
	namespace gui
	{
		namespace object
		{
			class object
			{
				public:
					int			i_;
					/** ctor
					 */
					object();
					std::shared_ptr<window>		get_window();
					/// render
					virtual void			draw() = 0;
					/** set label
					 */
					void			set_label( char const * cstr );
					/// x
					float		x_;
					float		y_;
					float		w_;
					float		h_;
					bool		active_;

					//std::shared_ptr< jess::signal::connection<int> >	connection_key_down_;
					/// key up
					//std::shared_ptr< jess::signal::connection<int> >	connection_key_up_;
					/// key_down
					/*		virtual int		handle_key(unsigned short,int) = 0;
							virtual int		handle_key_down(unsigned short) = 0;
					/// key_up
					virtual int		handle_key_up(unsigned short) = 0;*/
					//int			key_down_mask_;
					//int			key_up_mask_;
					size_t			label_length_;
					char *			label_;


					// connections
					struct
					{
						mouse_button_fun_c	mouse_button_fun_;
						key_fun_c		key_fun_;
					} conns_;


					virtual int				key_fun(int,int,int,int);
					virtual int				mouse_button_fun(int,int,int);

					virtual void				connect();

			};
		}
	}
}
#endif

