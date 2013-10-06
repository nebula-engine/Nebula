#include <nebula/content/actor/admin/actor.hpp>


ncaa::actor::actor() {
}
ncaa::actor::~actor() {
}
void	ncaa::actor::init( const jess::shared_ptr<nc_sc_a::base>& parent ) {
	//jess::clog << NEB_FUNCSIG << std::endl;
	ncaa::base::init(parent);
}
void	ncaa::actor::shutdown( ) {
	
}
void	ncaa::actor::update( ) {
	ncaa::base::update();
}
void	ncaa::actor::render( const jess::shared_ptr<npr::base>& rnd ) {
}
void	ncaa::actor::step( ) {
}




