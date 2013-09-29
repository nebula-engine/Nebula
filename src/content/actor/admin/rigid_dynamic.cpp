#include <nebula/content/actor/admin/rigid_dynamic.hpp>


		ncaa::rigid_dynamic::rigid_dynamic() {
}
		ncaa::rigid_dynamic::~rigid_dynamic() {
}



void	ncaa::rigid_dynamic::init( const boost::shared_ptr<>&  ) {
	PRINTSIG;
	ncaa::rigid_body::VInit( data );
}
void	ncaa::rigid_dynamic::VShutdown(Void* v) {
	PRINTSIG;
	
}
void	ncaa::rigid_dynamic::VUpdate(Void* v) {
	ncaa::rigid_body::VUpdate(v);
}
void	ncaa::rigid_dynamic::VRender( Void* data ) {
	PRINTSIG;
	
}
void	ncaa::rigid_dynamic::VStep( Void* data ) {
	PRINTSIG;
	
}




void	ncaa::rigid_dynamic::VCreateShape() {
	PRINTSIG;
	
}

















