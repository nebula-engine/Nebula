#include <math/free.h>

#include <neb/scene/desc.h>
#include <neb/actor/Base.h>

void neb::scene::raw::load(tinyxml2::XMLElement* element) {
	
	printf("%s\n",__PRETTY_FUNCTION__);
	
	gravity_.from_math(math::xml_parse_vec3(element->FirstChildElement("gravity"), math::vec3(0,0,0)));
}


void neb::scene::desc::load(char const* c) {
	
	printf("%s\n",__PRETTY_FUNCTION__);
	
	tinyxml2::XMLDocument doc;
	if(doc.LoadFile(c)) abort();
	
	load(doc.FirstChildElement("scene"));
}
void neb::scene::desc::load(tinyxml2::XMLElement* element) {

	printf("%s\n",__PRETTY_FUNCTION__);
	
	raw_.load(element);
	
	// actors
	tinyxml2::XMLElement* e = element->FirstChildElement("actor");
	
	std::shared_ptr<neb::actor::Base> actor;
	
	while(e)
	{
		glutpp::actor::desc* ad = new glutpp::actor::desc;
		
		ad->load(e);
		
		actors_.push_back(ad);
			
		e = e->NextSiblingElement("actor");
	}
}





