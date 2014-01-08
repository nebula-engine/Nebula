#include <math/free.h>

#include <glutpp/scene/desc.h>

//#include <neb/config.h>
//#include <neb/scene/desc.h>
//#include <neb/actor/Base.h>

void glutpp::scene::raw::reset() {
	GLUTPP_DEBUG_0_FUNCTION;

	//i_ = -1;
}
void glutpp::scene::raw::load(tinyxml2::XMLElement* element) {
	GLUTPP_DEBUG_0_FUNCTION;
	
	gravity_.from_math(math::xml_parse_vec3(element->FirstChildElement("gravity"), math::vec3(0,0,0)));
}



void glutpp::scene::id::write(gal::network::message_shared msg) {
	msg->write(&i_, sizeof(int));
}
void glutpp::scene::id::read(gal::network::message_shared msg) {
	msg->read(&i_, sizeof(int));
}
size_t glutpp::scene::id::size() {
	return sizeof(int);
}



glutpp::scene::desc::desc() {
	raw_.reset();
}
void glutpp::scene::desc::load(char const* c) {
	GLUTPP_DEBUG_0_FUNCTION;
	
	tinyxml2::XMLDocument doc;
	if(doc.LoadFile(c)) abort();
	
	load(doc.FirstChildElement("scene"));
}
void glutpp::scene::desc::load(tinyxml2::XMLElement* element) {
	GLUTPP_DEBUG_0_FUNCTION;
	
	raw_.load(element);
	
	// actors
	tinyxml2::XMLElement* e = element->FirstChildElement("actor");
	
	std::shared_ptr<glutpp::actor::actor> actor;
	
	while(e)
	{
		glutpp::actor::desc_shared ad(new glutpp::actor::desc);
		
		ad->load(e);
		
		actors_.push_back(ad);
			
		e = e->NextSiblingElement("actor");
	}
}
void glutpp::scene::desc::write(gal::network::message_shared msg) {
	GLUTPP_DEBUG_0_FUNCTION;
	
	assert(msg);
	
	size_t len = size() + sizeof(int);
	
	printf("len = %i\n", (int)len);
	
	// type
	//int type = glutpp::network::type::SCENE;
	
	//memcpy(head, &type, sizeof(int));
	//head += sizeof(int);
	
	// write scene raw
	//raw_.actor_size_ = actors_.size();
	
	//printf("actor_size_ = %i\n", (int)raw_.actor_size_);
	
	msg->write(&raw_, sizeof(glutpp::scene::raw));
	
	/*
	for(auto it = actors_.begin(); it != actors_.end(); ++it)
	{
		auto actor = *it;
		assert(actor);
		
		actor->write(head);
	}	
	
	msg->set(data, len);
	*/
}
void glutpp::scene::desc::read(gal::network::message_shared msg) {
	GLUTPP_DEBUG_0_FUNCTION;

	msg->write(&raw_, sizeof(glutpp::scene::raw));

	//printf("actor_size_ = %i\n", (int)raw_.actor_size_);
/*
	// actors
	for(size_t i = 0; i < raw_.actor_size_; ++i)
	{
		glutpp::actor::desc_shared ad(new glutpp::actor::desc);
		
		ad->read(head);
		
		actors_.push_back(ad);
	}
*/
}
size_t glutpp::scene::desc::size() {
	GLUTPP_DEBUG_0_FUNCTION;

	size_t s = sizeof(glutpp::scene::raw);
	
	for(auto it = actors_.begin(); it != actors_.end(); ++it)
	{
		auto actor = *it;
		
		assert(actor);
		
		s += actor->size();
	}
	
	return s;
}




