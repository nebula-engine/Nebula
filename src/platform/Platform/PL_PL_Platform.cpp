
#include <utilities/Types/Utilities.h>

#include <core/Core.h>


#include <Platform/Window/PL_WI_Window.h>
#include <Platform/Input/PI_IN_Input.h>

#include <framework/Communication/Message/FR_COM_MSG_Message.h>











#include <Platform/Platform/PL_PL_Platform.h>

		PL_PL_Platform::Platform() {
}
		PL_PL_Platform::~Platform() {
	
}
void	PL_PL_Platform::init( const boost::shared_ptr<>&  ) {
	PRINTSIG;
	
	m_app = DynCast<Void,AR_Init>( data )->app;

	m_keyDown[::Platform::Input::Key::Space] = Event::eDELETE_WINDOW;
}
void	PL_PL_Platform::VShutDown() {
	PRINTSIG;
	
	m_window.Clear();
}
void	PL_PL_Platform::VDeleteWindow( int windowNo ) {
	PRINTSIG;
	
	PL_WI_Window* window = m_window.Find( windowNo );

	if ( window ) {
		window->VShutDown();
		m_window.Erase( windowNo );
	}

	
}
void	PL_PL_Platform::VCreateWindow( PL_WI_Window*& window ) {
	PRINTSIG;
}
void	PL_PL_Platform::VUpdate() {
	//PRINTSIG;
	FR_COM_IComm::Update();

	m_window.For( &PL_WI_Window::VUpdate );
}
void	PL_PL_Platform::Process( FR_COM_MSG_Message* msg ) {
	PRINTSIG;
	
	printf("platform process\n");

	UINT key;
	UINT eventType;


	switch ( msg->type ) {
	case FR_COM_MSG_Type::eKEY_DOWN:

		key = msg->data.keyEventData.key;
		
		eventType = m_keyDown[key];

		ProcessEvent( eventType, msg );

	}

}
void	PL_PL_Platform::ProcessEvent( UINT eventType, FR_COM_MSG_Message* msg ) {
	int window;

	switch ( eventType ) {
	case Event::eDELETE_WINDOW:


		window = msg->data.keyEventData.window;

		VDeleteWindow(window);

		break;
	default:
		throw Except("unhandled event");
		break;
	}
}



