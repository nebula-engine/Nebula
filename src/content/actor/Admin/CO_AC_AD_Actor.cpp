#include <content/Actor/Admin/CO_AC_AD_Actor.h>

		CO_AC_AD_Actor::Actor() {
}
		CO_AC_AD_Actor::~Actor() {
}
void	CO_AC_AD_Actor::VInit(Void* v) {
	PRINTSIG;
	CO_AC_AD_ActorBase::VInit(v);
}
void	CO_AC_AD_Actor::VShutdown(Void* v) {
	
}
void	CO_AC_AD_Actor::VUpdate(Void* v) {
	CO_AC_AD_ActorBase::VUpdate(v);
}
void	CO_AC_AD_Actor::VRender(Void* v) {
}
void	CO_AC_AD_Actor::VStep(Void* v) {
}




