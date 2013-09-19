#include <utilities/Types/Utilities.h>

#include <Platform/Renderer/PL_RE_Renderer.h>
#include <Platform/Input/PI_IN_Input.h>
#include <content/Actor/Physics/CO_AC_PH_Controller.h>

#include <framework/Communication/Message/FR_COM_MSG_Message.h>
#include <framework/Communication/Message/FR_COM_MSG_Data.h>



#include <content/Actor/Physics/CO_AC_PH_Controller.h>
#include <content/Actor/Renderer/CO_AC_RE_Controller.h>




#include <content/Actor/Admin/CO_AC_AD_Controller.h>




		CO_AC_AD_Controller::Controller() {
}
		CO_AC_AD_Controller::~Controller(){
}
void	CO_AC_AD_Controller::VInit( Void* v ) {
	CO_AC_AD_ActorBase::VInit(v);



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
void	CO_AC_AD_Controller::VShutdown(Void* v) {
	PRINTSIG;
	
}
void	CO_AC_AD_Controller::VUpdate(Void* v) {
	CO_AC_AD_ActorBase::VUpdate(v);
}
void	CO_AC_AD_Controller::VStep(Void* v) {
	CO_AC_AD_ActorBase::VStep(v);

	Ptr<CO_AC_PH_Controller>::Get_Or_Error()->VStep(v);
}
void	CO_AC_AD_Controller::VRender(Void* v) {
}
void	CO_AC_AD_Controller::Process( FR_COM_MSG_Message* msg ) {
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
void	CO_AC_AD_Controller::MouseMove( int x, int y ) {
	//PRINTSIG;
	
	m_a_yaw   -= x * 0.001;
	m_a_pitch -= y * 0.001;
}
void	CO_AC_AD_Controller::VLookAt(Void* v) {
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
void	CO_AC_AD_Controller::ProcessEvent(UINT evnt)
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































