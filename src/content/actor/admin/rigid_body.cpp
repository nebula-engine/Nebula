
#include <nebula/content/actor/admin/rigid_body.h>



		ncaa::rigid_body::rigid_body() {
}
		ncaa::rigid_body::~rigid_body() {
}


void	ncaa::rigid_body::VInit( Void* data ) {
	PRINTSIG;
	ncaa::rigid_actor::VInit( data );

	
}
void	ncaa::rigid_body::VShutdown(Void* v) {
	PRINTSIG;
	
}
void	ncaa::rigid_body::VUpdate(Void* v) {
	ncaa::rigid_actor::VUpdate(v);
}
void	ncaa::rigid_body::VRender( Void* data ) {
	PRINTSIG;
	
}
void	ncaa::rigid_body::VStep( Void* data ) {
	PRINTSIG;
	
}


void	ncaa::rigid_body::VCreateShape() {
}



