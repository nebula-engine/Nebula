#include <utilities/Casting.h>

#include <Network/Network.h>

		Network::Network() {
	
}
		Network::~Network() {
}
void	Network::init( v) {
	AR_Init* i = DynCast<Void,AR_Init>(v);
	
	Ptr<FR_App>::Set_Or_Error(i->app);
}
void	Network::Shutdown( v) {
	
}
void	Network::Update( v) {
	
}








