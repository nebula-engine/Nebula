#include <nebula/define.hpp>
#include <nebula/content/actor/admin/rigid_body.hpp>



ncaa::rigid_body::rigid_body()
{

}
ncaa::rigid_body::~rigid_body()
{

}
void	ncaa::rigid_body::init( jess::shared_ptr<nc_sc_a::base> parent )
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
void	ncaa::rigid_body::render( jess::shared_ptr<npr::base> rnd )
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;
	
	ncaa::rigid_actor::render( rnd );
}
void	ncaa::rigid_body::step(FLOAT) {
	//jess::clog << NEB_FUNCSIG << std::endl;
	
}
void	ncaa::rigid_body::create_shapes()
{
}



