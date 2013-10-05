#include <nebula/content/actor/physics/rigid_actor.hpp>

namespace nca = nebula::content::actor;

ncap::rigid_actor::rigid_actor()
{
}
ncap::rigid_actor::~rigid_actor()
{
}
ncap::rigid_actor::rigid_actor( const ncap::rigid_actor& act )
{
}
ncap::rigid_actor&	ncap::rigid_actor::operator=( const ncap::rigid_actor& act )
{
	return *this;
}
void	ncap::rigid_actor::init( boost::shared_ptr<nca::admin::base>& parent )
{
	ncap::actor::init( parent );
}
void	ncap::rigid_actor::shutdown()
{
	
}
void	ncap::rigid_actor::update()
{
	
}
void	ncap::rigid_actor::step(FLOAT dt)
{
	
}
void	ncap::rigid_actor::render( const boost::shared_ptr<npr::base>& rnd )
{

}
void	ncap::rigid_actor::create_shapes()
{

}







