#include <utilities/Types/UT_TY_LN_Actor.h>

#include <content/Actor/Admin/CO_AC_AD_Controller.h>




#include <content/Actor/Physics/CO_AC_PH_Controller.h>

		CO_AC_PH_Controller::Controller() {
}
		CO_AC_PH_Controller::~Controller() {
}
void	CO_AC_PH_Controller::VInit(Void* v)
{
	AR_Init* i = DynCast<Void,AR_Init>(v);

	Ptr<CO_AC_AD_Controller>::Set_Or_Error(i->co_ac_ad_controller);
	
}
void	CO_AC_PH_Controller::VShutdown(Void* v) {
	
}
void	CO_AC_PH_Controller::VUpdate(Void* v) {
	
}
void	CO_AC_PH_Controller::VStep(Void* v) {
	AR_Step* s = DynCast<Void,AR_Step>(v);
	
	CO_AC_AD_Controller* controller = Ptr<CO_AC_AD_Controller>::Get_Or_Error();

	UpdateMove();

	// create rotation
	Math::Vec4f yaw( Math::Vec3f(0,1,0), controller->m_a_yaw );
	
	/// transform m_move into global frame
	controller->m_move *= yaw;
	
	controller->m_pos += controller->m_move * s->dt;
}
void	CO_AC_PH_Controller::UpdateMove() {
	CO_AC_AD_Controller* controller = Ptr<CO_AC_AD_Controller>::Get_Or_Error();


	/// TODO: add gravity

	/// TODO: make static member variables
	FLOAT s = 1;
	FLOAT d = 0.707;

	s *= 1.5;
	d *= 1.5;

	FLOAT h000 = s;
	FLOAT h045 = d;
	FLOAT h090 = s;
	FLOAT h135 = d;
	FLOAT h180 = s;
	FLOAT h225 = d;
	FLOAT h270 = s;
	FLOAT h315 = d;

	map<int,Math::Vec3f> m;
	m[CO_AC_AD_Controller::Flag::eFORWARD] =										Math::Vec3f(  0,    0, -h000 );
	m[CO_AC_AD_Controller::Flag::eFORWARD	| CO_AC_AD_Controller::Flag::eRIGHT] =	Math::Vec3f(  h045, 0, -h045 );
	m[CO_AC_AD_Controller::Flag::eRIGHT] =											Math::Vec3f(  h090, 0,  0 );
	m[CO_AC_AD_Controller::Flag::eBACKWARD	| CO_AC_AD_Controller::Flag::eRIGHT] =	Math::Vec3f(  h135, 0,  h135 );
	m[CO_AC_AD_Controller::Flag::eBACKWARD] =										Math::Vec3f(  0,    0,  h180 );
	m[CO_AC_AD_Controller::Flag::eBACKWARD	| CO_AC_AD_Controller::Flag::eLEFT] =	Math::Vec3f( -h225, 0,  h225 );
	m[CO_AC_AD_Controller::Flag::eLEFT] =											Math::Vec3f( -h270, 0,  0 );
	m[CO_AC_AD_Controller::Flag::eFORWARD	| CO_AC_AD_Controller::Flag::eLEFT] =	Math::Vec3f( -h315, 0, -h315 );

	/// find vector for move flag
	auto it = m.find(controller->m_flag);
	
	if ( it != m.end() ) {
		controller->m_move = it->second;

		//printf("move ");
		//controller->m_move.print();
	}
	else {
		controller->m_move = Math::Vec3f();

		//printf("default move ");
		//controller->m_move.print();
	}
}








