#include <content/Actor/Renderer/CO_AC_RE_ActorBase.h>



		CO_AC_RE_ActorBase::ActorBase() {
	
}
		CO_AC_RE_ActorBase::~ActorBase() {
}


void	CO_AC_RE_ActorBase::VInit( Void* data ){
	m_app = DynCast<Void,AR_Init>( data )->app;
}
void	CO_AC_RE_ActorBase::VShutDown(){
	
}
void	CO_AC_RE_ActorBase::VUpdate(){
	
}
void	CO_AC_RE_ActorBase::VRender( Void* data ) {
	
}
void	CO_AC_RE_ActorBase::VStep( Void* data ){
	
}












