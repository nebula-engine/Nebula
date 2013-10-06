#include <nebula/asio/message.hpp>

#include <nebula/asio/mailbox.hpp>

void						na::mailbox::update()
{
	while ( !messages_.empty() )
	{
		process_message( messages_.front() );
		messages_.pop_front();
	}
}
void						na::mailbox::push_back( jess::shared_ptr<na::message> msg )
{
	messages_.push_back( msg );
}
jess::shared_ptr<na::message>			na::mailbox::pop_front()
{
	jess::shared_ptr<na::message> msg;
	
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


