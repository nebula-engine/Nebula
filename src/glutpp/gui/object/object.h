#ifndef __NEBULA_UI_OBJECT_BASE_HPP__
#define __NEBULA_UI_OBJECT_BASE_HPP__

#include <memory>

#include <linux/input.h>

#include <SIG/connection.h>


namespace GUL
{
namespace object
{
	/** \brief base
	 */
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
			virtual int						handle_key(__u16,__s32) = 0;
			virtual int						handle_key_down(__u16) = 0;
			/// key_up
			virtual int						handle_key_up(__u16) = 0;
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

#endif

