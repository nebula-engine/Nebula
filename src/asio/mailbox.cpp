#include <nebula/asio/message.hpp>

#include <nebula/asio/mailbox.hpp>

void						n40000::mailbox::update()
{
	while ( !messages_.empty() )
	{
		process_message( messages_.front() );
		messages_.pop_front();
	}
}
void						n40000::mailbox::push_back( std::shared_ptr<n40000::message> msg )
{
	messages_.push_back( msg );
}
std::shared_ptr<n40000::message>		n40000::mailbox::pop_front()
{
	std::shared_ptr<n40000::message> msg;
	
	if ( messages_.empty() )
	{
		return msg;
	}
	else
	{
		msg = messages_.front();
		messages_.pop_front();
		return msg;
	}
}


