#include <nebula/content/actor/physics/rigid_dynamic.hpp>

namespace nca = nebula::content::actor;

nca::physics::rigid_dynamic::rigid_dynamic()
{
}
nca::physics::rigid_dynamic::~rigid_dynamic()
{
}
ncap::rigid_dynamic::rigid_dynamic( const ncap::rigid_dynamic& act )
{

}
ncap::rigid_dynamic&	ncap::rigid_dynamic::operator=( const ncap::rigid_dynamic& act )
{
	return *this;
}
void	nca::physics::rigid_dynamic::init( jess::shared_ptr<nca::admin::base> parent )
{
	ncap::rigid_body::init( parent );
}
void	nca::physics::rigid_dynamic::shutdown()
{
	
}
void	nca::physics::rigid_dynamic::update()
{
	
}
void	nca::physics::rigid_dynamic::step(FLOAT)
{

}
void	ncap::rigid_dynamic::render( jess::shared_ptr<npr::base> rnd )
{

}
void	ncap::rigid_dynamic::create_shape()
{

}








