#include <nebula/content/actor/admin/rigid_dynamic.hpp>


		ncaa::rigid_dynamic::rigid_dynamic()
{
}
		ncaa::rigid_dynamic::~rigid_dynamic()
{
}
void	ncaa::rigid_dynamic::init( const jess::shared_ptr<nc_sc_a::base>& parent )
{
	//jess::clog << NEB_FUNCSIG << std::endl;
	ncaa::rigid_body::init( parent );
}
void	ncaa::rigid_dynamic::shutdown()
{
	//jess::clog << NEB_FUNCSIG << std::endl;
}
void	ncaa::rigid_dynamic::update()
{
	ncaa::rigid_body::update();
}
void	ncaa::rigid_dynamic::render( const jess::shared_ptr<npr::base>& rnd )
{
	//jess::clog << NEB_FUNCSIG << std::endl;
	
}
void	ncaa::rigid_dynamic::step( FLOAT dt )
{
	//jess::clog << NEB_FUNCSIG << std::endl;
	
}
void	ncaa::rigid_dynamic::create_shapes()
{
	//jess::clog << NEB_FUNCSIG << std::endl;
	
}

















