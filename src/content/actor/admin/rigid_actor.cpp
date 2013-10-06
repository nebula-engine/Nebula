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
void	ncaa::rigid_actor::init( const jess::shared_ptr<nc_sc_a::base>& parent )
{
	ncaa::actor::init( parent );

	create_shape();
}
void	ncaa::rigid_actor::render( const jess::shared_ptr<npr::base>& rnd )
{
	shapes_.foreach( boost::bind( &ncsa::base::render, _1, rnd ) );
}
void	ncaa::rigid_actor::create_shape()
{
	
}
void	ncaa::rigid_actor::create_box( const jess::shared_ptr<ncsa::box>& bx )
{
	//shapes_.push<ncsa::box>( bx, boost::bind( &ncsa::box::init, _1, shared_from_this() ) );
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


