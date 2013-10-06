#include <nebula/framework/app.hpp>

#include <nebula/content/base.hpp>
#include <nebula/content/physics/base.hpp>
#include <nebula/content/actor/admin/rigid_actor.hpp>
#include <nebula/content/shape/admin/box.hpp>

#include <nebula/content/actor/renderer/rigid_actor.hpp>

ncar::rigid_actor::rigid_actor()
{

}
ncar::rigid_actor::~rigid_actor()
{

}
void	ncar::rigid_actor::init( const jess::shared_ptr<ncaa::base>& parent )
{
	ncar::actor::init( parent );
}
void	ncar::rigid_actor::shutdown()
{
}
void	ncar::rigid_actor::update()
{
}
void	ncar::rigid_actor::render( const jess::shared_ptr<npr::base>& rnd )
{
	jess::shared_ptr<ncaa::rigid_actor> parent = std::dynamic_pointer_cast<ncaa::rigid_actor>( parent_.lock() );

	parent->shapes_.foreach( std::bind( &ncsa::base::render, std::placeholders::_1, rnd ) );
}
void	ncar::rigid_actor::step( FLOAT dt )
{

}
void	ncar::rigid_actor::create_shapes()
{

}

