#ifndef __NEBULA_UI_OBJECT_BASE_HPP__
#define __NEBULA_UI_OBJECT_BASE_HPP__

#include <memory>

#include <gal/sig/connection.h>

namespace glutpp
{
	namespace gui
	{
		namespace object
		{
			class object
			{
				public:
					/** ctor
					*/
					object();
					/// render
					virtual void						Display() = 0;
					/** set label
					*/
					void							set_label( char const * cstr );
					/// x
					unsigned int						x_;
					/// y
					unsigned int						y_;
					/// w
					unsigned int						w_;
					/// h
					unsigned int						h_;
					/** \brief active
					*/
					bool							active_;
					/// key down
					//std::shared_ptr< jess::signal::connection<int> >	connection_key_down_;
					/// key up
					//std::shared_ptr< jess::signal::connection<int> >	connection_key_up_;
					/// key_down
					virtual int				handle_key(unsigned short,int) = 0;
					virtual int				handle_key_down(unsigned short) = 0;
					/// key_up
					virtual int				handle_key_up(unsigned short) = 0;
					/** \brief key down mask
					*/
					int							key_down_mask_;
					/** \brief key up mask
					*/
					int							key_up_mask_;
					/** label length
					*/
					size_t							label_length_;
					/** \brief label
					*/
					char *							label_;
			};
		}
	}
}
#endif

