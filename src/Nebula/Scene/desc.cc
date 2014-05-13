#include <fstream>

#include <boost/archive/xml_iarchive.hpp>

#include <Nebula/Actor/Util/desc.hpp>
#include <Nebula/scene/desc.hpp>
#include <Nebula/scene/scene.hpp>


Neb::Scene::desc::desc(): raw_wrapper_(Neb::master::global()->factories_.scene_raw_) {
}
void Neb::Scene::desc::load(char const* filename) {
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
void		Neb::Scene::desc::load(Neb::weak_ptr<Neb::Scene::scene> scene) {
	i_ = scene->i_;
	*raw_wrapper_.ptr_ = *scene->raw_;
	
	// now
	for(auto it = scene->actors_.begin(); it != scene->actors_.end(); ++it) {
		//auto actor = it->second;
		
		boost::shared_ptr<Neb::Actor::desc> ad(new Neb::Actor::desc);
		
		ad->load(it->second);
		
		ad->getRaw()->mode_create_ = Neb::Actor::mode_create::NOW;

		actors_.push_back(ad);
	}

	// deferred
	for(auto it = scene->actors_deferred_.begin(); it != scene->actors_deferred_.end(); ++it) {
		//auto desc = it->second;

		boost::shared_ptr<Neb::Actor::desc> ad(new Neb::Actor::desc);
		
		auto w = it->second;
		auto s = w.lock();
		
		*ad = *s;

		ad->getRaw()->mode_create_ = Neb::Actor::mode_create::DEFERRED;

		actors_.push_back(ad);
	}
}





