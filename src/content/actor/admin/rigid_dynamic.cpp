#include <nebula/define.hpp>
#include <nebula/content/actor/admin/rigid_dynamic.hpp>


ncaa::rigid_dynamic::rigid_dynamic()
{
}
ncaa::rigid_dynamic::~rigid_dynamic()
{
}
void	ncaa::rigid_dynamic::init( jess::shared_ptr<nc_sc_a::base> parent )
{
	jess::clog << NEB_FUNCSIG << std::endl;
	
	ncaa::rigid_body::init( parent );
}
void	ncaa::rigid_dynamic::shutdown()
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
void	ncaa::rigid_dynamic::update()
{
	ncaa::rigid_body::update();
}
void	ncaa::rigid_dynamic::render( jess::shared_ptr<npr::base> rnd )
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;
	
	ncaa::rigid_body::render( rnd );
}
void	ncaa::rigid_dynamic::step( FLOAT dt )
{
	jess::clog << NEB_FUNCSIG << std::endl;
	
}
void	ncaa::rigid_dynamic::create_shapes()
{
	jess::clog << NEB_FUNCSIG << std::endl;
	
}

















