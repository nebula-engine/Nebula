#ifndef __NEBULA_PLATFORM_JOYSTICK_HPP__
#define __NEBULA_PLATFORM_JOYSTICK_HPP__

namespace nebula
{
	namespace platform
	{
		namespace joystick
		{
			/** \brief event structure
			*/
			struct event
			{
				/** \brief time
				*/
				unsigned int	time;
				/** \brief value
				*/
				short		value;
				/** \brief type
				*/
				unsigned char	type;
				/** \brief number
				*/
				unsigned char	number;
			};
			/** \brief xbox
			*/
			struct status_xbox
			{
				/** \brief button
				*/
				int		button[11];
				/** \brief x
				*/
				int		x;
				/** \brief y
				*/
				int		y;
			};
			/** \brief base
			*/
			class base
			{
				protected:
					/** \brief copy ctor
					*/
					base( base const & ) = default;
					/** \brief assignment
					*/
					base&			operator=( base const & ) = default;
					/** \brief ctor
					*/
					base( n21000::base::shared_t );
				public:
					/** \brief open
					*/
					void			open();
					/** \brief close
					*/
					void			close();
				protected:

			};
		}
	}
}

#endif
