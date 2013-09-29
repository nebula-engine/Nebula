#include <nebula/content/actor/admin/actor.hpp>


ncaa::actor::actor() {
}
ncaa::actor::~actor() {
}
void	ncaa::actor::VInit(Void* v) {
	PRINTSIG;
	ncaa::base::VInit(v);
}
void	ncaa::actor::VShutdown(Void* v) {
	
}
void	ncaa::actor::VUpdate(Void* v) {
	ncaa::base::VUpdate(v);
}
void	ncaa::actor::VRender(Void* v) {
}
void	ncaa::actor::VStep(Void* v) {
}




