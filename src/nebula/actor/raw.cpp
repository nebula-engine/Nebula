#include <nebula/actor/raw.hpp>

neb::actor::raw::raw():
	health_(1.0)
{

}
void neb::actor::raw::load(tinyxml2::XMLElement* element) {
	glutpp::actor::raw::load(element);
	
	// filtering
        parse_filtering(element);
}
void neb::actor::raw::load(glutpp::actor::actor_s actor) {
	glutpp::actor::raw::load(actor);


}



