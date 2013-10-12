#include <nebula/define.hpp>
#include <nebula/content/actor/admin/rigid_static.hpp>


n34100::rigid_static::rigid_static( jess::shared_ptr<n32100::base> parent ):
rigid_actor( parent )
{
}
n34100::rigid_static::~rigid_static()
{
}
void	n34100::rigid_static::init()
{
	jess::clog << NEB_FUNCSIG << std::endl;
	
	n34100::rigid_actor::init();
}
void	n34100::rigid_static::shutdown()
{
	jess::clog << NEB_FUNCSIG << std::endl;
	
}
void	n34100::rigid_static::update()
{
	jess::clog << NEB_FUNCSIG << std::endl;
	
}
void	n34100::rigid_static::render( jess::shared_ptr<n23000::base> rnd )
{
	jess::clog << NEB_FUNCSIG << std::endl;
	
}
void	n34100::rigid_static::step( float dt )
{
	jess::clog << NEB_FUNCSIG << std::endl;
	
}



void	n34100::rigid_static::VCreateShape() {
	
}





