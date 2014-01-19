#include <math/free.h>

#include <glutpp/scene/desc.h>
#include <glutpp/scene/scene.h>


glutpp::scene::desc::desc()
{
}
void glutpp::scene::desc::load(char const* c) {
	GLUTPP_DEBUG_0_FUNCTION;
	
	tinyxml2::XMLDocument doc;
	if(doc.LoadFile(c))
	{
		printf("error loading %s\n", c);
		abort();
	}
	
	load(doc.FirstChildElement("scene"));
}
void glutpp::scene::desc::load(tinyxml2::XMLElement* element) {
	GLUTPP_DEBUG_0_FUNCTION;
	
	get_raw()->load(element);
	
	// actors
	tinyxml2::XMLElement* e = element->FirstChildElement("actor");
	
	std::shared_ptr<glutpp::actor::actor<>> actor;
	
	while(e)
	{
		glutpp::actor::desc_s ad(new glutpp::actor::desc);
		
		ad->load(e);
		
		get_actors()->vec_.push_back(std::make_tuple(ad));
			
		e = e->NextSiblingElement("actor");
	}
}

glutpp::scene::id_s glutpp::scene::desc::get_id() {
	auto id = std::get<2>(tup_);
	assert(id);	
	return id;
}
glutpp::scene::raw_s glutpp::scene::desc::get_raw() {
	auto raw = std::get<1>(tup_);
	assert(raw);	
	return raw;
}
glutpp::scene::vec_actor_desc_s glutpp::scene::desc::get_actors() {
	auto a = std::get<0>(tup_);
	assert(a);	
	return a;
}


