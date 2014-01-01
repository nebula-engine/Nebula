

#include <neb/scene_desc.h>


void neb::scene_desc::load(tinyxml2::XMLElement* element) {

	printf("%s\n",__PRETTY_FUNCTION__);
	
	gravity = math::xml_parse_vec3(el_scene->FirstChildElement("gravity"), math::vec3(0,0,0));
	
	// actors

	load_actors(element);
}
void neb::scene_desc::load_actors(tinyxml2::XMLElement* element) {
	
	tinyxml2::XMLElement* e = element->FirstChildElement("actor");
	
	std::shared_ptr<neb::actor::Base> actor;
	
	int i = 0;
	while(e)
	{
		actors_[i].load(e);
		
		//actor = Create_Actor(el_actor, parent);
		
		// recursivly create children
		Create_Actors(el_actor, actor);
		Create_Lights(el_actor, actor);
		
		el_actor = el_actor->NextSiblingElement("actor");
	}
}





