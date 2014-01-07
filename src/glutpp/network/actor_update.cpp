#include <glutpp/network/actor_update.h>

void glutpp::network::actor_update::write(gal::network::message_shared msg) {
	
	msg->write(&scene_i_, sizeof(int));
	
	actors_.write(msg);
}
void glutpp::network::actor_update::read(gal::network::message_shared msg) {
	
	msg->read(&scene_i_, sizeof(int));
	
	actors_.read(msg);
}
size_t glutpp::network::actor_update::size() {
	
	size_t s = sizeof(int) + actors_.size();
}



