#include <content/Actor/Admin/CO_AC_AD_RigidDynamic.h>


		CO_AC_AD_RigidDynamic::RigidDynamic() {
}
		CO_AC_AD_RigidDynamic::~RigidDynamic() {
}



void	CO_AC_AD_RigidDynamic::VInit( Void* data ) {
	PRINTSIG;
	CO_AC_AD_RigidBody::VInit( data );
}
void	CO_AC_AD_RigidDynamic::VShutdown(Void* v) {
	PRINTSIG;
	
}
void	CO_AC_AD_RigidDynamic::VUpdate(Void* v) {
	CO_AC_AD_RigidBody::VUpdate(v);
}
void	CO_AC_AD_RigidDynamic::VRender( Void* data ) {
	PRINTSIG;
	
}
void	CO_AC_AD_RigidDynamic::VStep( Void* data ) {
	PRINTSIG;
	
}




void	CO_AC_AD_RigidDynamic::VCreateShape() {
	PRINTSIG;
	
}

















