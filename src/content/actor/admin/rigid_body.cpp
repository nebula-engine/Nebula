#include <utilities/Types/Utilities.h>

#include <content/Actor/Admin/CO_AC_AD_RigidBody.h>



		CO_AC_AD_RigidBody::RigidBody() {
}
		CO_AC_AD_RigidBody::~RigidBody() {
}


void	CO_AC_AD_RigidBody::VInit( Void* data ) {
	PRINTSIG;
	CO_AC_AD_RigidActor::VInit( data );

	
}
void	CO_AC_AD_RigidBody::VShutdown(Void* v) {
	PRINTSIG;
	
}
void	CO_AC_AD_RigidBody::VUpdate(Void* v) {
	CO_AC_AD_RigidActor::VUpdate(v);
}
void	CO_AC_AD_RigidBody::VRender( Void* data ) {
	PRINTSIG;
	
}
void	CO_AC_AD_RigidBody::VStep( Void* data ) {
	PRINTSIG;
	
}


void	CO_AC_AD_RigidBody::VCreateShape() {
}



