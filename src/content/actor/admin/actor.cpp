#include <nebula/define.hpp>

#include <nebula/content/actor/admin/actor.hpp>


ncaa::actor::actor() {
}
ncaa::actor::~actor() {
}
void	ncaa::actor::init( jess::shared_ptr<nc_sc_a::base> parent )
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;
	
	// init parent
	ncaa::base::init( parent );

	jess::shared_ptr<ncaa::base> this_ptr( shared_from_this() );
}
void	ncaa::actor::shutdown( )
{
	
}
void	ncaa::actor::update( )
{
	ncaa::base::update();
}
void	ncaa::actor::render( jess::shared_ptr<npr::base>& rnd )
{
	
}
void	ncaa::actor::step( FLOAT dt )
{
	jess::clog << NEB_FUNCSIG << std::endl;
	
	ncaa::base::step( dt );
}




