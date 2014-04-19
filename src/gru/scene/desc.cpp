#include <math/free.hpp>

#include <gru/scene/desc.hpp>
#include <gru/scene/scene.hpp>


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
	
	while(e)
	{
		glutpp::actor::desc_s ad(new glutpp::actor::desc);
		
		ad->load(e);
		
		get_actors()->vec_.push_back(std::make_tuple(ad));
			
		e = e->NextSiblingElement("actor");
	}
}
void glutpp::scene::desc::load(glutpp::scene::scene_s scene) {
	get_id()->load(scene);
	get_raw()->load(scene);

	// now
	for(auto it = scene->actors_.begin(); it != scene->actors_.end(); ++it)
	{
		auto actor = it->second;

		glutpp::actor::desc_s ad(new glutpp::actor::desc);

		ad->load(actor);

		ad->get_raw()->mode_create_ = glutpp::actor::mode_create::NOW;

		get_actors()->vec_.push_back(std::make_tuple(ad));
	}

	// deferred
	for(auto it = scene->actors_deferred_.begin(); it != scene->actors_deferred_.end(); ++it)
	{
		auto desc = it->second;

		glutpp::actor::desc_s ad(new glutpp::actor::desc);

		*ad = *desc;

		ad->get_raw()->mode_create_ = glutpp::actor::mode_create::DEFERRED;

		get_actors()->vec_.push_back(std::make_tuple(ad));
	}
}	
glutpp::scene::id_s glutpp::scene::desc::get_id() {
	auto id = std::get<0>(tup_);
	assert(id);	
	return id;
}
glutpp::scene::raw_s glutpp::scene::desc::get_raw() {
	auto raw = std::get<1>(tup_);
	assert(raw);	
	return raw;
}
glutpp::scene::vec_actor_desc_s glutpp::scene::desc::get_actors() {
	auto a = std::get<2>(tup_);
	assert(a);	
	return a;
}


