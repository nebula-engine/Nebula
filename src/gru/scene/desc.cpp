//#include <math/free.hpp>

#include <fstream>

#include <boost/archive/xml_iarchive.hpp>

#include <gru/actor/desc.hpp>
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
void		glutpp::scene::desc::load(Neb::weak_ptr<glutpp::scene::scene> scene) {
	i_ = scene->i_;
	raw_wrapper_.ptr_ = scene->raw_;
	
	// now
	for(auto it = scene->actors_.begin(); it != scene->actors_.end(); ++it) {
		//auto actor = it->second;
		
		boost::shared_ptr<glutpp::actor::desc> ad(new glutpp::actor::desc);
		
		ad->load(it->second);
		
		ad->getRaw()->mode_create_ = glutpp::actor::mode_create::NOW;

		actors_.push_back(ad);
	}

	// deferred
	for(auto it = scene->actors_deferred_.begin(); it != scene->actors_deferred_.end(); ++it) {
		//auto desc = it->second;

		boost::shared_ptr<glutpp::actor::desc> ad(new glutpp::actor::desc);

		*ad = *(it->second);

		ad->getRaw()->mode_create_ = glutpp::actor::mode_create::DEFERRED;

		actors_.push_back(ad);
	}
}





