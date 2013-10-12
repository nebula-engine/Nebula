#include <nebula/define.hpp>

#include <nebula/content/actor/admin/actor.hpp>


n34100::actor::actor() {
}
n34100::actor::~actor() {
}
void	n34100::actor::init( jess::shared_ptr<n32100::base> parent )
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;
	
	// init parent
	n34100::base::init( parent );

	jess::shared_ptr<n34100::base> this_ptr( shared_from_this() );
}
void	n34100::actor::shutdown( )
{
	
}
void	n34100::actor::update( )
{
	n34100::base::update();
}
void	n34100::actor::render( jess::shared_ptr<n23000::base> rnd )
{
	
}
void	n34100::actor::step( float dt )
{
	jess::clog << NEB_FUNCSIG << std::endl;
	
	n34100::base::step( dt );
}




