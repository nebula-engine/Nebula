#include <glutpp/scene/desc.h>
#include <glutpp/scene/scene.h>

void glutpp::scene::addr::write(gal::network::message_shared msg) {
	vec_.write(msg);
}
void glutpp::scene::addr::read(gal::network::message_shared msg) {
	vec_.read(msg);
}
size_t glutpp::scene::addr::size() {
	return vec_.size();
}



void glutpp::scene::addr::load(glutpp::scene::scene_shared scene) {
	
	vec_.vec_.clear();
	
	vec_.vec_.push_back(scene->i());
	
}

//gal::network::vector<int>	vec_;

