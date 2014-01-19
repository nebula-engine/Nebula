#include <glutpp/scene/scene.h>
#include <glutpp/actor/actor.h>



glutpp::scene::addr_s glutpp::actor::addr::get_scene_addr() {
	auto p = std::get<1>(tup_);
	assert(p);
	return p;
}
glutpp::actor::vec_int_s glutpp::actor::addr::get_vec() {
	auto p = std::get<0>(tup_);
	assert(p);
	return p;

}



