//#include <math/free.hpp>

#include <fstream>

#include <boost/archive/xml_iarchive.hpp>

#include <gru/scene/desc.hpp>
#include <gru/scene/scene.hpp>


glutpp::scene::desc::desc()
{
}
void glutpp::scene::desc::load(char const* filename) {
	GLUTPP_DEBUG_0_FUNCTION;

	/*	
	tinyxml2::XMLDocument doc;
	if(doc.LoadFile(c))
	{
		printf("error loading %s\n", c);
		abort();
	}
	*/
	std::ifstream ifs(filename);
	assert(ifs.good());
	boost::archive::xml_iarchive ia(ifs);
	
	serialize(ia,0);
	//ia >> *this;

//	load(doc.FirstChildElement("scene"));
}
/*
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
}*/
void glutpp::scene::desc::load(glutpp::scene::scene_s scene) {
	i_ = scene->i_;
	raw_ = scene->raw_;

	// now
	for(auto it = scene->actors_.begin(); it != scene->actors_.end(); ++it)
	{
		auto actor = it->second;

		boost::shared_ptr<glutpp::actor::desc> ad(new glutpp::actor::desc);

		ad->load(actor);

		ad->raw_.mode_create_ = glutpp::actor::mode_create::NOW;

		actors_.push_back(ad);
	}

	// deferred
	for(auto it = scene->actors_deferred_.begin(); it != scene->actors_deferred_.end(); ++it)
	{
		auto desc = it->second;

		boost::shared_ptr<glutpp::actor::desc> ad(new glutpp::actor::desc);

		*ad = *desc;

		ad->raw_.mode_create_ = glutpp::actor::mode_create::DEFERRED;

		actors_.push_back(ad);
	}
}





