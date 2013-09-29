


#include <nebula/content/actor/admin/base.hpp>

		ncaa::base::base() {
	
}
		ncaa::base::~base() {
}
void	ncaa::base::VInit(Void* v) {
	PRINTSIG;

	Ptr<CO_SC_AD_Scene>::Set_Or_Error( DynCast<Void,AR_Init>(v)->scene );
}
void	ncaa::base::VShutdown(Void* v) {
	PRINTSIG;
}
void	ncaa::base::VUpdate(Void* v) {
	FR_COM_IComm::Update();
}
void	ncaa::base::VRender( Void* data ) {
	PRINTSIG;
}
void	ncaa::base::VStep(Void* v)
{
	
}


void	ncaa::base::GetTransform( Math::Transformf& trans ) {
	trans = m_transform;
}
void	ncaa::base::SetTransform( Math::Transformf& trans ) {
	m_transform = trans;
}












