
#include <Platform/Renderer/PL_RE_Renderer.h>
#include <utilities/Types/Utilities.h>

#include <content/Actor/Admin/CO_AC_AD_Controller.h>




#include <content/Actor/Renderer/CO_AC_RE_Controller.h>

		CO_AC_RE_Controller::Controller() {
}
		CO_AC_RE_Controller::~Controller() {
}


void	CO_AC_RE_Controller::VInit( Void* data ){
	CO_AC_RE_ActorBase::VInit(data);
}
void	CO_AC_RE_Controller::VShutDown(){
	
}
void	CO_AC_RE_Controller::VUpdate(){
	
}
void	CO_AC_RE_Controller::VRender(Void* v) {
	AR_Render* r = DynCast<Void,AR_Render>(v);

	CO_AC_AD_Controller* controller = L__CO_AC_AD_Controller::Get_Or_Error<CO_AC_AD_Controller>();

	r->renderer->VLookAt( controller->m_pos, controller->m_pos + controller->m_look, controller->m_up );
}
void	CO_AC_RE_Controller::VStep( Void* data ){
	
}




























