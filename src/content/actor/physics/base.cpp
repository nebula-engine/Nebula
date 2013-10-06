#include <nebula/content/actor/physics/base.hpp>

/// \todo completely separate "platform" from the rest of "nebula"


nca::physics::base::base()
{
}
nca::physics::base::~base()
{
}
nca::physics::base::base( const ncap::base& act )
{
}
nca::physics::base&	ncap::base::operator=( const ncap::base& act )
{
	return *this;
}
void	nca::physics::base::init( jess::shared_ptr<nebula::content::actor::admin::base>& parent )
{
	parent_ = parent;
}
void	nca::physics::base::shutdown()
{
	
}
void	nca::physics::base::update()
{
	
}
void	nca::physics::base::step()
{
	
}
void	ncap::base::render( jess::shared_ptr<npr::base> rnd )
{

}
void	ncap::base::create_shapes()
{

}





