


#include <content/Actor/Admin/CO_AC_AD_ActorBase.h>

		CO_AC_AD_ActorBase::ActorBase() {
	
}
		CO_AC_AD_ActorBase::~ActorBase() {
}
void	CO_AC_AD_ActorBase::VInit(Void* v) {
	PRINTSIG;

	Ptr<CO_SC_AD_Scene>::Set_Or_Error( DynCast<Void,AR_Init>(v)->scene );
}
void	CO_AC_AD_ActorBase::VShutdown(Void* v) {
	PRINTSIG;
}
void	CO_AC_AD_ActorBase::VUpdate(Void* v) {
	FR_COM_IComm::Update();
}
void	CO_AC_AD_ActorBase::VRender( Void* data ) {
	PRINTSIG;
}
void	CO_AC_AD_ActorBase::VStep(Void* v)
{
	
}


void	CO_AC_AD_ActorBase::GetTransform( Math::Transformf& trans ) {
	trans = m_transform;
}
void	CO_AC_AD_ActorBase::SetTransform( Math::Transformf& trans ) {
	m_transform = trans;
}












