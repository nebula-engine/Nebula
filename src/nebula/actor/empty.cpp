#include <neb/config.h>
#include <neb/actor/empty.h>

neb::actor::empty::empty(glutpp::parent_s parent):
	neb::actor::Base(parent)
{
	NEBULA_DEBUG_0_FUNCTION;
}
void neb::actor::empty::init(glutpp::actor::desc_s desc) {
	
	NEBULA_DEBUG_0_FUNCTION;
	
	neb::actor::Base::init(desc);
}
void neb::actor::empty::create_physics(std::shared_ptr<neb::shape> shape) {
	
	NEBULA_DEBUG_0_FUNCTION;
	printf("not implemented\n");
}
void neb::actor::empty::create_physics() {
	
	NEBULA_DEBUG_0_FUNCTION;
	printf("not implemented\n");
}
void neb::actor::empty::init_physics() {
	
	NEBULA_DEBUG_0_FUNCTION;
	printf("not implemented\n");
}



