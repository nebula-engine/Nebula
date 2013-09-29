#include <utilities/Types/Utilities.h>

#include <Platform/Renderer/PL_RE_Renderer.h>
#include <Platform/Input/PI_IN_Input.h>
#include <content/actor/Physics/CO_AC_PH_Controller.h>

#include <framework/Communication/Message/FR_COM_MSG_Message.h>
#include <framework/Communication/Message/FR_COM_MSG_Data.h>



#include <content/actor/Physics/CO_AC_PH_Controller.h>
#include <content/actor/Renderer/CO_AC_RE_Controller.h>




#include <nebula/content/actor/admin/ncaa::Controller.h>




		ncaa::Controller::Controller() {
}
		ncaa::Controller::~Controller(){
}
void	ncaa::Controller::VInit( Void* v ) {
	ncaa::base::VInit(v);



	AR_Init* i = DynCast<Void,AR_Init>(v);

	i->co_ac_ad_controller = this;



	m_flag = 0;

	m_a_yaw = 0;
	m_a_pitch = 0;

	m_pos = Math::Vec3f(0,0,5);


	m_key_flag[Platform::Input::Key::w] = Flag::eFORWARD;
	m_key_flag[Platform::Input::Key::s] = Flag::eBACKWARD;
	m_key_flag[Platform::Input::Key::a] = Flag::eLEFT;
	m_key_flag[Platform::Input::Key::d] = Flag::eRIGHT;

	// physics
	Ptr<CO_AC_PH_Controller>::Set_Or_Error( new CO_AC_PH_Controller() );

	Ptr<CO_AC_PH_Controller>::Get_Or_Error()->VInit(v);
	// renderer
	Ptr<CO_AC_RE_Controller>::Set_Or_Error( new CO_AC_RE_Controller() );

	Ptr<CO_AC_RE_Controller>::Get_Or_Error()->VInit(v);
}
void	ncaa::Controller::VShutdown(Void* v) {
	PRINTSIG;
	
}
void	ncaa::Controller::VUpdate(Void* v) {
	ncaa::base::VUpdate(v);
}
void	ncaa::Controller::VStep(Void* v) {
	ncaa::base::VStep(v);

	Ptr<CO_AC_PH_Controller>::Get_Or_Error()->VStep(v);
}
void	ncaa::Controller::VRender(Void* v) {
}
void	ncaa::Controller::Process( FR_COM_MSG_Message* msg ) {
	//PRINTSIG;
	UINT key;
	UINT flag;
	UINT evnt;

	switch ( msg->type ) {
	case FR_COM_MSG::Type::eKEY_UP:
		key = msg->data.keyEventData.key;

		// set flag
		flag = m_key_flag[key];
		m_flag &= ~( flag );

		// trigger event
		evnt = m_key_up_event[key];
		if ( evnt != Event::eINVALID ) 

		break;
	case FR_COM_MSG::Type::eKEY_DOWN:
		key = msg->data.keyEventData.key;
		
		// unset flag
		flag = m_key_flag[key];
		m_flag |= flag;



		// reset pointer position
		if ( msg->data.keyEventData.key == Platform::Input::Key::r ) {
			
		}
		
		break;
	case FR_COM_MSG::Type::eMOUSE_MOVE:

		MouseMove( msg->data.mouse_move.x, msg->data.mouse_move.y );

		break;
	default:
		throw Except("Unhandled message");
		break;
	}
}
void	ncaa::Controller::MouseMove( int x, int y ) {
	//PRINTSIG;
	
	m_a_yaw   -= x * 0.001;
	m_a_pitch -= y * 0.001;
}
void	ncaa::Controller::VLookAt(Void* v) {
	Math::Vec4f rot(0,0,0,1);

	Math::Vec4f yaw(	Math::Vec3f(0,1,0), m_a_yaw );
	Math::Vec4f pitch(	Math::Vec3f(1,0,0), m_a_pitch );

	rot *= pitch;
	rot *= yaw;

	m_up = Math::Vec3f(0,1,0);
	m_look = Math::Vec3f(0,0,-1);

	m_up *= rot;
	m_look *= rot;

	AR_Render* r = DynCast<Void,AR_Render>(v);

	r->renderer->VLookAt( m_pos, m_pos + m_look, m_up );
}
void	ncaa::Controller::ProcessEvent(UINT evnt)
{
	switch ( evnt )
	{
	case Event::eRESET_VIEW_ANGLE:
		printf("reset viewing angles\n");
		m_a_yaw = 0;
		m_a_pitch = 0;
		break;
	}
}































