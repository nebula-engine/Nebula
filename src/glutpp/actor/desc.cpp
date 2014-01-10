#include <math/free.h>

//#include <neb/physics.h>
//#include <neb/scene/scene.h>
//#include <neb/simulation_callback.h>
#include <glutpp/actor/desc.h>
#include <glutpp/actor/actor.h>





void glutpp::actor::desc::load(tinyxml2::XMLElement* element) {
	GLUTPP_DEBUG_0_FUNCTION;
	
	raw_.load(element);
	
	// shapes
	tinyxml2::XMLElement* element_shape = element->FirstChildElement("shape");
	glutpp::shape::desc_shared sd;

	while(element_shape != NULL)
	{
		sd.reset(new glutpp::shape::desc);

		sd->load(element_shape);

		shapes_.vec_.push_back(std::make_tuple(sd));

		element_shape = element->NextSiblingElement("shape");
	}

}
void glutpp::actor::desc::load(glutpp::actor::actor_shared actor) {
	GLUTPP_DEBUG_0_FUNCTION;

	i_ = actor->i_;
	raw_ = actor->raw_;

	// shape
	glutpp::shape::desc_shared sd;
	for(auto it = actor->shapes_.begin(); it != actor->shapes_.end(); ++it)
	{
		auto shape = it->second;
		
		sd.reset(new glutpp::shape::desc);
		
		sd->load(shape);
		
		shapes_.vec_.push_back(std::make_tuple(sd));
	}

	// actor
	glutpp::actor::desc_shared ad;
	for(auto it = actor->actors_.begin(); it != actor->actors_.end(); ++it)
	{
		auto a = it->second;
		
		ad.reset(new glutpp::actor::desc);
		
		ad->load(a);
		
		actors_.vec_.push_back(std::make_tuple(ad));
	}

}
void glutpp::actor::desc::read(gal::network::message_shared msg) {

	printf("%s\n",__PRETTY_FUNCTION__);

	msg->read(&i_, sizeof(int));

	msg->read(&raw_, sizeof(glutpp::actor::raw));

	shapes_.read(msg);
	actors_.read(msg);

	printf("shape_size_ = %i\n", (int)shapes_.vec_.size());
	printf("actor_size_ = %i\n", (int)actors_.vec_.size());
}
void glutpp::actor::desc::write(gal::network::message_shared msg) {
	GLUTPP_DEBUG_0_FUNCTION;

	msg->write(&i_, sizeof(int));

	msg->write(&raw_, sizeof(glutpp::actor::raw));

	shapes_.write(msg);
	actors_.write(msg);

	printf("shape_size_ = %i\n", (int)shapes_.vec_.size());
	printf("actor_size_ = %i\n", (int)actors_.vec_.size());
}
size_t glutpp::actor::desc::size() {
	GLUTPP_DEBUG_0_FUNCTION;

	size_t s;

	s += sizeof(int);
	s += sizeof(glutpp::actor::raw);
	s += shapes_.size();
	s += actors_.size();

	return s;
}



