#include <nebula/define.hpp>
#include <nebula/content/actor/admin/rigid_body.hpp>



n34100::rigid_body::rigid_body()
{

}
n34100::rigid_body::~rigid_body()
{

}
void	n34100::rigid_body::init( jess::shared_ptr<n32100::base> parent )
{
	//jess::clog << NEB_FUNCSIG << std::endl;
	n34100::rigid_actor::init( parent );
}
void	n34100::rigid_body::shutdown() {
	//jess::clog << NEB_FUNCSIG << std::endl;
	
}
void	n34100::rigid_body::update() {
	n34100::rigid_actor::update();
}
void	n34100::rigid_body::render( jess::shared_ptr<n23000::base> rnd )
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;
	
	n34100::rigid_actor::render( rnd );
}
void	n34100::rigid_body::step( float dt )
{
	jess::clog << NEB_FUNCSIG << std::endl;

	n34100::rigid_actor::step( dt );	
}
void	n34100::rigid_body::create_shapes()
{
}



