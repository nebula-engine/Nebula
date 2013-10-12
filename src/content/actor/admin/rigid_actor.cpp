#include <nebula/framework/app.hpp>

#include <nebula/platform/renderer/scoped_matrix.hpp>

#include <nebula/content/base.hpp>
#include <nebula/content/physics/base.hpp>
#include <nebula/content/actor/physics/rigid_actor.hpp>
#include <nebula/content/shape/admin/base.hpp>
#include <nebula/content/shape/admin/box.hpp>

#include <nebula/content/actor/admin/rigid_actor.hpp>

n34100::rigid_actor::rigid_actor()
{
}
n34100::rigid_actor::~rigid_actor()
{
}
void	n34100::rigid_actor::init( jess::shared_ptr<n32100::base> parent )
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;
	
	n34100::actor::init( parent );

	jess::shared_ptr<n34100::base> this_ptr( shared_from_this() );
	
	create_shapes();
}
void	n34100::rigid_actor::render( jess::shared_ptr<n23000::base> rnd )
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

	{
		n23000::scoped_matrix scoepd_matrix( rnd );
		
		rnd->mult_matrix( pose_ );
		
		shapes_.foreach( std::bind( &n35100::base::render, std::placeholders::_1, rnd ) );
	}
}
void	n34100::rigid_actor::create_shapes()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;
}
jess::shared_ptr<n35100::box>	n34100::rigid_actor::create_box()
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;

	// cast shared_from_this
	jess::shared_ptr<n34100::rigid_actor> this_ptr = std::dynamic_pointer_cast<n34100::rigid_actor>( shared_from_this() );
	
	// create
	jess::shared_ptr<n35100::box> bx( new n35100::box );
	
	shapes_.push<n35100::box>( bx );//, std::bind( &n35100::box::init, std::placeholders::_1, this_ ) );
	
	bx->init( this_ptr );
	
	return bx;
}
jess::shared_ptr<ncsa::box>	ncaa::rigid_actor::create_plane()
{
	jess::clog << NEB_FUNCSIG << std::endl;

	// cast shared_from_this
	jess::shared_ptr<ncaa::rigid_actor> this_ptr = std::dynamic_pointer_cast<ncaa::rigid_actor>( shared_from_this() );
	
	// create
	jess::shared_ptr<ncsa::plane> plane( new ncsa::plane );
	
	shapes_.push<ncsa::plane>( plane );//, std::bind( &ncsa::box::init, std::placeholders::_1, this_ ) );
	
	plane->init( this_ptr );
	
	return plane;
}
void	ncaa::rigid_actor::shutdown()
{
	
}
void	n34100::rigid_actor::update()
{
	n34100::actor::update();
}
void	n34100::rigid_actor::step( float dt )
{
	jess::clog << NEB_FUNCSIG << std::endl;

	n34100::actor::step( dt );
}


