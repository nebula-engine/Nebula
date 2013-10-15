#ifndef __NEBULA_ASIO_MESSAGE_HPP__
#define __NEBULA_ASIO_MESSAGE_HPP__

namespace nebula
{
	namespace asio
	{
		/** \brief %message
		*/
		class message
		{
			public:
				/** \brief %size
				*/
				int		size_;
				/** \brief %buffer
				*/
				char		buffer[512];

		};
	}
}

#endif

