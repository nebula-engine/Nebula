#include <nebula/content/actor/admin/rigid_body.hpp>



		ncaa::rigid_body::rigid_body() {
}
		ncaa::rigid_body::~rigid_body() {
}


void	ncaa::rigid_body::init( const jess::shared_ptr<nc_sc_a::base>& parent )
{
	//jess::clog << NEB_FUNCSIG << std::endl;
	ncaa::rigid_actor::init( parent );

	
}
void	ncaa::rigid_body::shutdown() {
	//jess::clog << NEB_FUNCSIG << std::endl;
	
}
void	ncaa::rigid_body::update() {
	ncaa::rigid_actor::update();
}
void	ncaa::rigid_body::render(const jess::shared_ptr<npr::base>&) {
	//jess::clog << NEB_FUNCSIG << std::endl;
	
}
void	ncaa::rigid_body::step(FLOAT) {
	//jess::clog << NEB_FUNCSIG << std::endl;
	
}
void	ncaa::rigid_body::create_shapes()
{
}



