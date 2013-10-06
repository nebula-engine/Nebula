#include <nebula/framework/app.hpp>

#include <nebula/content/base.hpp>
#include <nebula/content/physics/base.hpp>
#include <nebula/content/actor/physics/rigid_actor.hpp>
#include <nebula/content/actor/physics/physx/rigid_actor.hpp>
#include <nebula/content/shape/admin/base.hpp>
#include <nebula/content/shape/admin/box.hpp>

#include <nebula/content/actor/admin/rigid_actor.hpp>

ncaa::rigid_actor::rigid_actor()
{
}
ncaa::rigid_actor::~rigid_actor()
{
}
void	ncaa::rigid_actor::init( jess::shared_ptr<nc_sc_a::base> parent )
{
	// log
	jess::clog << NEB_FUNCSIG << std::endl;
	
	ncaa::actor::init( parent );

	jess::shared_ptr<ncaa::base> this_ptr( shared_from_this() );
	
	create_shape();
}
void	ncaa::rigid_actor::render( jess::shared_ptr<npr::base>& rnd )
{
	shapes_.foreach( std::bind( &ncsa::base::render, std::placeholders::_1, rnd ) );
}
void	ncaa::rigid_actor::create_shape()
{
	
}
void	ncaa::rigid_actor::create_box( jess::shared_ptr<ncsa::box>& bx )
{
	jess::shared_ptr<ncaa::rigid_actor> this_ = std::dynamic_pointer_cast<ncaa::rigid_actor>( shared_from_this() );

	shapes_.push<ncsa::box>( bx, std::bind( &ncsa::box::init, std::placeholders::_1, this_ ) );
}
void	ncaa::rigid_actor::shutdown()
{
	
}
void	ncaa::rigid_actor::update()
{
	ncaa::actor::update();
}
void	ncaa::rigid_actor::step() {
	
}


