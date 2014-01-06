#include <neb/actor/Actor.h>
#include <neb/active_transform.h>


void neb::active_transform::node::write(char*& head) {
	
	memcpy(head, &raw_, sizeof(neb::active_transform::node_raw));
	head += sizeof(neb::active_transform::node_raw);
}
void neb::active_transform::node::read(char*& head) {
	
	memcpy(&raw_, head, sizeof(neb::active_transform::node_raw));
	head += sizeof(neb::active_transform::node_raw);
}
size_t neb::active_transform::node::size() {
	
	size_t s = sizeof(neb::active_transform::node_raw);

	return s;
}


neb::active_transform::set::set() {
	
	raw_.name_scene_ = -1;
}
void neb::active_transform::set::push_back(neb::actor::Actor* a) {
	
	node* n = new node;
	
	n->raw_.name_ = a->desc_->raw_.i_;
	n->raw_.pose_ = a->desc_->raw_.pose_;
	
	nodes_.push_back(n);
}
std::shared_ptr<gal::network::message> neb::active_transform::set::serialize() {
	
	std::shared_ptr<gal::network::message> msg(new gal::network::message);
	
	size_t len = size() + sizeof(int);
	
	char* data = new char[len];
	char* head = data;
	
	int type = neb::network::type::ACTIVE_TRANSFORM_SET;
	
	memcpy(head, &type, sizeof(int));
	head += sizeof(int);
	
	write(head);
	
	msg->set(data, len);
	
	return msg;
}
void neb::active_transform::set::write(char*& head) {

	raw_.node_size_ = nodes_.size();
	
	memcpy(head, &raw_, sizeof(neb::active_transform::set_raw));
	head += sizeof(neb::active_transform::set_raw);
	
	// nodes
	for(auto it = nodes_.begin(); it != nodes_.end(); ++it)
	{
		auto n = *it;
		
		n->write(head);
	}
}
void neb::active_transform::set::read(char*& head) {
	
	memcpy(&raw_, head, sizeof(neb::active_transform::set_raw));
	head += sizeof(neb::active_transform::set_raw);

	printf("node_size_ = %i\n", (int)raw_.node_size_);
	
	// nodes
	for(size_t i = 0; i < raw_.node_size_; ++i)
	{
		node* n = new node;
		
		n->read(head);
		
		nodes_.push_back(n);
	}
	
}
size_t neb::active_transform::set::size() {
	
	size_t s = sizeof(neb::active_transform::set_raw);
	
	for(auto it = nodes_.begin(); it != nodes_.end(); ++it)
	{
		auto n = *it;
		
		s += n->size();
	}

	return s;
}

