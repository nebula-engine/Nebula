#include <math/free.h>

#include <glutpp/scene/desc.h>

//#include <neb/config.h>
//#include <neb/scene/desc.h>
//#include <neb/actor/Base.h>

void glutpp::scene::raw::reset() {
	
	printf("%s\n",__PRETTY_FUNCTION__);
	
	i_ = -1;
	
}
void glutpp::scene::raw::load(tinyxml2::XMLElement* element) {
	
	printf("%s\n",__PRETTY_FUNCTION__);
	
	gravity_.from_math(math::xml_parse_vec3(element->FirstChildElement("gravity"), math::vec3(0,0,0)));
}


glutpp::scene::desc::desc() {
	raw_.reset();
}
void glutpp::scene::desc::load(char const* c) {
	
	printf("%s\n",__PRETTY_FUNCTION__);
	
	tinyxml2::XMLDocument doc;
	if(doc.LoadFile(c)) abort();
	
	load(doc.FirstChildElement("scene"));
}
void glutpp::scene::desc::load(tinyxml2::XMLElement* element) {

	printf("%s\n",__PRETTY_FUNCTION__);
	
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
gal::network::message::shared_t glutpp::scene::desc::serialize() {

	GLUTPP_DEBUG_0_FUNCTION;
	
	gal::network::message::shared_t msg(new gal::network::message);
	
	size_t len = size() + sizeof(int);

	printf("len = %i\n", (int)len);
	
	// alloc
	char* data = new char[len];
	char* head = data;
	
	// type
	int type = glutpp::network::type::SCENE;
	
	memcpy(head, &type, sizeof(int));
	head += sizeof(int);
	
	// write scene raw
	raw_.actor_size_ = actors_.size();

	printf("actor_size_ = %i\n", (int)raw_.actor_size_);
	
	memcpy(head, &raw_, sizeof(glutpp::scene::raw));
	head += sizeof(glutpp::scene::raw);
	
	for(auto it = actors_.begin(); it != actors_.end(); ++it)
	{
		auto actor = *it;
		assert(actor);
		
		actor->write(head);
	}	
	
	msg->set(data, len);
	
	//NEBULA_DEBUG_0_FUNCTION;

	return msg;
}
void glutpp::scene::desc::read(char*& data) {
	
	printf("%s\n",__PRETTY_FUNCTION__);
	
	char* head = data;
	
	memcpy(&raw_, head, sizeof(glutpp::scene::raw));
	head += sizeof(glutpp::scene::raw);

	printf("actor_size_ = %i\n", (int)raw_.actor_size_);

	// actors
	for(size_t i = 0; i < raw_.actor_size_; ++i)
	{
		glutpp::actor::desc_shared ad(new glutpp::actor::desc);
		
		ad->read(head);
		
		actors_.push_back(ad);
	}
}
size_t glutpp::scene::desc::size() {
	
	size_t s = sizeof(glutpp::scene::raw);
	
	for(auto it = actors_.begin(); it != actors_.end(); ++it)
	{
		auto actor = *it;
		
		assert(actor);
		
		s += actor->size();
	}
	
	return s;
}




