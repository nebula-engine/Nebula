#include <nebula/asio/message.hpp>


#include <nebula/platform/key.hpp>
#include <nebula/platform/window/base.hpp>
#include <nebula/platform/platform/base.hpp>

npp::base::base()
{

}
npp::base::~base()
{
	
}
void	npp::base::init( const boost::shared_ptr<nf::app>& parent )
{
	//PRINTSIG;
	parent_ = parent;
	
	key_down_event_[np::key::space] = event::eDELETE_WINDOW;
}
void	npp::base::shutdown() {
	//PRINTSIG;
	
	windows_.clear();
}
void	npp::base::delete_window( int window_no )
{
	//PRINTSIG;
	
	boost::shared_ptr<npw::base> wnd = windows_.at( window_no );
	
	if ( wnd )
	{
		wnd->shutdown();
		windows_.erase( window_no );
	}

	
}
void	npp::base::create_window( boost::shared_ptr<npw::base>& wnd )
{
	//PRINTSIG;
}
void	npp::base::update()
{
	//PRINTSIG;
	//FR_COM_IComm::Update();
	mailbox::update();

	windows_.foreach( boost::bind( &npw::base::update, _1 ) );
}
void	npp::base::process_message( boost::shared_ptr<na::message> msg )
{
	//PRINTSIG;
	
	//printf("platform process\n");

	//int k;
	//int evnt;
	
	
	switch ( msg->type_ )
	{
	/*
	case ns::message::type::eKEY_DOWN:

		key = msg->data.keyEventData.key;
		
		eventType = m_keyDown[key];

		ProcessEvent( eventType, msg );
	*/
	}

}
void	npp::base::process_event( int evnt )
{
	//int window_no;
	
	switch ( evnt )
	{
	case event::eDELETE_WINDOW:
		//window = msg->data.keyEventData.window;
		
		//VDeleteWindow(window);

		break;
	default:
		//throw Except("unhandled event");
		break;
	}
}



