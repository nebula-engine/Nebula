#include <nebula/content/actor/physics/rigid_body.hpp>


nca::physics::rigid_body::rigid_body()
{

}
nca::physics::rigid_body::~rigid_body()
{

}
nca::physics::rigid_body::rigid_body( const ncap::rigid_body& act )
{

}
nca::physics::rigid_body&	ncap::rigid_body::operator=( const ncap::rigid_body& act )
{
	return *this;
}
void	nca::physics::rigid_body::init(const boost::shared_ptr<nca::admin::base>& parent)
{
	nca::physics::rigid_actor::init(parent);
}
void	nca::physics::rigid_body::shutdown()
{
	
}
void	nca::physics::rigid_body::update()
{
	
}
void	nca::physics::rigid_body::step(FLOAT dt)
{
	
}
void	ncap::rigid_body::render( const boost::shared_ptr<npr::base>& rnd )
{

}








