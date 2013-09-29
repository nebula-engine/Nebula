#include <nebula/content/actor/admin/ncaa::RigidDynamic.h>


		ncaa::RigidDynamic::RigidDynamic() {
}
		ncaa::RigidDynamic::~RigidDynamic() {
}



void	ncaa::RigidDynamic::VInit( Void* data ) {
	PRINTSIG;
	ncaa::rigid_body::VInit( data );
}
void	ncaa::RigidDynamic::VShutdown(Void* v) {
	PRINTSIG;
	
}
void	ncaa::RigidDynamic::VUpdate(Void* v) {
	ncaa::rigid_body::VUpdate(v);
}
void	ncaa::RigidDynamic::VRender( Void* data ) {
	PRINTSIG;
	
}
void	ncaa::RigidDynamic::VStep( Void* data ) {
	PRINTSIG;
	
}




void	ncaa::RigidDynamic::VCreateShape() {
	PRINTSIG;
	
}

















