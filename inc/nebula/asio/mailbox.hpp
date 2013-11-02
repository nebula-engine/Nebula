#ifndef __NEBULA_ASIO_MAILBOX_HPP__
#define __NEBULA_ASIO_MAILBOX_HPP__

#include <memory>
#include <deque>


#include <nebula/ns.hpp>

namespace nebula
{
	namespace asio
	{
		class mailbox
		{
		public:
			virtual void									update();
			virtual void									push_back( std::shared_ptr<n40000::message> );
			std::shared_ptr<n40000::message>						pop_front();
			virtual void									process_message( std::shared_ptr<n40000::message> ) = 0;
			
			std::deque< std::shared_ptr<n40000::message> >					messages_;
		};
	}
}

#endif
