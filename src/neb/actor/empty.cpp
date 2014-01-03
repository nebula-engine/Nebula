#include <neb/config.h>
#include <neb/actor/empty.h>

neb::actor::empty::empty(
		glutpp::actor::desc* desc,
		std::shared_ptr<neb::scene::scene> scene,
		std::shared_ptr<neb::actor::Base> actor):
	neb::actor::Base(desc, scene, actor)
{
	NEBULA_DEBUG_0_FUNCTION;
}
void neb::actor::empty::init() {
	
	NEBULA_DEBUG_0_FUNCTION;
	
	neb::actor::Base::init();
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



