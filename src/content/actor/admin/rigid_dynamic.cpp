#include <nebula/define.hpp>
#include <nebula/content/actor/admin/rigid_dynamic.hpp>


n34100::rigid_dynamic::rigid_dynamic()
{
}
n34100::rigid_dynamic::~rigid_dynamic()
{
}
void	n34100::rigid_dynamic::init( jess::shared_ptr<n32100::base> parent )
{
	jess::clog << NEB_FUNCSIG << std::endl;
	
	n34100::rigid_body::init( parent );
}
void	n34100::rigid_dynamic::shutdown()
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
void	n34100::rigid_dynamic::update()
{
	n34100::rigid_body::update();
}
void	n34100::rigid_dynamic::render( jess::shared_ptr<n23000::base> rnd )
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;
	
	n34100::rigid_body::render( rnd );
}
void	n34100::rigid_dynamic::step( float dt )
{
	jess::clog << NEB_FUNCSIG << std::endl;

	n34100::rigid_body::step( dt );
}
void	n34100::rigid_dynamic::create_shapes()
{
	jess::clog << NEB_FUNCSIG << std::endl;
	
}

















