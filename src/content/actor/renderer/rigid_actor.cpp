#include <boost/bind.hpp>

#include <nebula/content/base.hpp>
#include <nebula/content/physics/base.hpp>

#include <nebula/content/actor/admin/rigid_actor.hpp>

#include <nebula/content/shape/admin/box.hpp>

#include <nebula/framework/app.hpp>

#include <nebula/content/actor/renderer/rigid_actor.hpp>

ncar::rigid_actor::rigid_actor()
{

}
ncar::rigid_actor::~rigid_actor()
{

}
void	ncar::rigid_actor::init( const boost::shared_ptr<ncaa::base>& parent )
{
	ncar::actor::init( parent );
}
void	ncar::rigid_actor::shutdown()
{
}
void	ncar::rigid_actor::update()
{
}
void	ncar::rigid_actor::render( const boost::shared_ptr<npr::base>& rnd )
{
	boost::shared_ptr<ncaa::rigid_actor> parent = boost::dynamic_pointer_cast<ncaa::rigid_actor>( parent_.lock() );

	parent->shapes_.foreach( boost::bind( &ncsa::base::render, _1, rnd ) );
}
void	ncar::rigid_actor::step( FLOAT dt )
{

}
void	ncar::rigid_actor::create_shapes()
{

}

