#include <nebula/asio/message.hpp>

#include <nebula/define.hpp>
#include <nebula/platform/key.hpp>
#include <nebula/platform/window/base.hpp>
#include <nebula/platform/platform/base.hpp>

n21000::base::base()
{

}
n21000::base::~base()
{

}
void	n21000::base::init( jess::shared_ptr<n10000::app> parent )
{
	//jess::clog << NEB_FUNCSIG << std::endl;
	parent_ = parent;

	key_down_event_[n20000::key::space] = event::eDELETE_WINDOW;
}
void	n21000::base::shutdown() {
	//jess::clog << NEB_FUNCSIG << std::endl;

	windows_.clear();
}
void	n21000::base::delete_window( int window_no )
{
	//jess::clog << NEB_FUNCSIG << std::endl;

	jess::shared_ptr<n22000::base> wnd = windows_.at( window_no );

	if ( wnd )
	{
		wnd->shutdown();
		windows_.erase( window_no );
	}


}
jess::shared_ptr<n22000::base>	n21000::base::create_window()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

	/// \todo make this pure virtual

	return jess::shared_ptr<n22000::base>();
}
void	n21000::base::update()
{
	//jess::clog << NEB_FUNCSIG << std::endl;
	//FR_COM_IComm::Update();
	mailbox::update();

	windows_.foreach( std::bind( &n22000::base::update, std::placeholders::_1 ) );
}
jess::shared_ptr<n22000::base>	n21000::base::request_window()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

	/**
	 *  \todo
	 *  The idea of request_window was that the platform could deal out existing windows.
	 *  However, trading of windows should take place between the objects which own the
	 *  windows (i.e. view, ui, etc.) (possibly coordinated by the user-defined app or something, not the platform).
	 **/
	return create_window();
}
void	n21000::base::process_message( jess::shared_ptr<n40000::message> msg )
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
void	n21000::base::process_event( int evnt )
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



