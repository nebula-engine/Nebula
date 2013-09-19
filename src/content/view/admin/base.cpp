#include <framework/FR_Mappable.h>








#include <content/View/Admin/CO_VI_AD_View.h>


		CO_VI_AD_View::View() {
	
	
}
		CO_VI_AD_View::~View() {
}
void	CO_VI_AD_View::VInit( Void* data ) {
	PRINTSIG;

	m_app =		DynCast<Void,AR_Init>( data )->app;
	m_scene =	DynCast<Void,AR_Init>( data )->scene;
}
void	CO_VI_AD_View::VShutDown() {
	PRINTSIG;
}
void	CO_VI_AD_View::VUpdate() {
}

