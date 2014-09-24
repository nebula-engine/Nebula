//#include <gru/config.hpp>

//#include <nebula/network/actor_release.hpp>
/*
neb::packet::actor_release::actor_release(int scene_i):
	scene_i_(scene_i)
{
}
std::shared_ptr<gal::network::message> neb::packet::actor_release::serialize() {
	std::shared_ptr<gal::network::message> msg(new gal::network::message);
	
	int len = sizeof(int) + size();
	
	char* data = new char[len];
	char* head = data;
	
	int type = glutpp::network::type::ACTOR_RELEASE;
	
	memcpy(head, &type, sizeof(int));
	head += sizeof(int);
	
	write(head);
	
	msg->set(data, len);
	
	return msg;
}
void neb::packet::actor_release::write(char*& head) {

	memcpy(head, &scene_i_, sizeof(int));
	head += sizeof(int);
	
	int actor_size_ = actor_i_.size();
	
	memcpy(head, &actor_size_, sizeof(int));
	head += sizeof(int);
	
	for(auto it = actor_i_.begin(); it != actor_i_.end(); ++it)
	{
		int i = *it;
		memcpy(head, &i, sizeof(int));
		head += sizeof(int);
	}
	
}
void neb::packet::actor_release::read(char*& head) {
	
	memcpy(&scene_i_, head, sizeof(int));
	head += sizeof(int);
	
	memcpy(&actor_size_, head, sizeof(int));
	head += sizeof(int);
	
	actor_i_.clear();
	int actor_i;
	for(int i = 0; i < actor_size_; ++i)
	{
		memcpy(&actor_i, head, sizeof(int));
		head += sizeof(int);
		
		actor_i_.push_back(actor_i);
	}
}
size_t neb::packet::actor_release::size() {
	
	int len = sizeof(int) + sizeof(int) + sizeof(int) * actor_i_.size();
	
	return len;
}

*/

