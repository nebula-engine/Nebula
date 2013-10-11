#include <nebula/content/actor/renderer/rigid_static_plane.hpp>

ncar::rigid_static_plane::rigid_static_plane()
{

}
ncar::rigid_static_plane::~rigid_static_plane()
{

}
void	ncar::rigid_static_plane::init( jess::shared_ptr<ncaa::base> parent )
{
	
}
void	ncar::rigid_static_plane::shutdown()
{
	
}
void	ncar::rigid_static_plane::update()
{
	
}
void	ncar::rigid_static_plane::render( jess::shared_ptr<npr::base> rnd )
{
	jess::shared_ptr<ncaa::base> parent = parent_.lock();
	
	rnd->push_matrix();
	
	rnd->mult_matrix(   )
	
	rnd->pop_matrix();
}
void	ncar::rigid_static_plane::step( )
{
	
}



