#include <neb/config.h>
#include <neb/actor/empty.h>

neb::actor::empty::empty(
		std::shared_ptr<neb::scene::scene> scene,
		std::shared_ptr<neb::actor::Base> actor):
	neb::actor::Base(scene, actor)
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



