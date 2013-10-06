#include <nebula/asio/message.hpp>

#include <nebula/define.hpp>
#include <nebula/platform/key.hpp>
#include <nebula/platform/window/base.hpp>
#include <nebula/platform/platform/base.hpp>

npp::base::base()
{

}
npp::base::~base()
{
	
}
void	npp::base::init( const jess::shared_ptr<nf::app>& parent )
{
	//jess::clog << NEB_FUNCSIG << std::endl;
	parent_ = parent;
	
	key_down_event_[np::key::space] = event::eDELETE_WINDOW;
}
void	npp::base::shutdown() {
	//jess::clog << NEB_FUNCSIG << std::endl;
	
	windows_.clear();
}
void	npp::base::delete_window( int window_no )
{
	//jess::clog << NEB_FUNCSIG << std::endl;
	
	jess::shared_ptr<npw::base> wnd = windows_.at( window_no );
	
	if ( wnd )
	{
		wnd->shutdown();
		windows_.erase( window_no );
	}

	
}
void	npp::base::create_window( jess::shared_ptr<npw::base>& wnd )
{
	//jess::clog << NEB_FUNCSIG << std::endl;
}
void	npp::base::update()
{
	//jess::clog << NEB_FUNCSIG << std::endl;
	//FR_COM_IComm::Update();
	mailbox::update();

	windows_.foreach( std::bind( &npw::base::update, std::placeholders::_1 ) );
}
void	npp::base::request_window( jess::shared_ptr<npw::base>& wnd )
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

	create_window( wnd );
}
void	npp::base::process_message( jess::shared_ptr<na::message> msg )
{
	//jess::clog << NEB_FUNCSIG << std::endl;
	
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



