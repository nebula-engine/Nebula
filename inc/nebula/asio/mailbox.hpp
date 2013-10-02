#ifndef __NEBULA_ASIO_MAILBOX_HPP__
#define __NEBULA_ASIO_MAILBOX_HPP__

#include <deque>

#include <boost/shared_ptr.hpp>

#include <nebula/utilities/types/asio/types.hpp>

#include <nebula/ns.hpp>

namespace nebula
{
	namespace asio
	{
		class mailbox
		{
		public:
			virtual void									update();
			virtual void									push_back( boost::shared_ptr<na::message> );
			boost::shared_ptr<na::message>							pop_front();
			
			std::deque< boost::shared_ptr<na::message> >					messages_;
		};
	}
}

#endif
