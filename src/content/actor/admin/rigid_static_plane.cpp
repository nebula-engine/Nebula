#include <nebula/content/actor/admin/rigid_static_plane.hpp>


		ncaa::rigid_static_plane::rigid_static_plane() {
}
		ncaa::rigid_static_plane::~rigid_static_plane() {
}




void	ncaa::rigid_static_plane::init( jess::shared_ptr<nc_sc_a::base> parent )
{
	//jess::clog << NEB_FUNCSIG << std::endl;
	ncaa::rigid_static::init( parent );

	physics_.reset( new ncap::rigid_static_plane() );
	physics_->init( shared_from_this() );

	renderer_.reset( new ncar::rigid_static_plane );
	renderer_->init( shared_from_this() );
	
}
void	ncaa::rigid_static_plane::shutdown() {
	//jess::clog << NEB_FUNCSIG << std::endl;
	
}
void	ncaa::rigid_static_plane::update() {
	//jess::clog << NEB_FUNCSIG << std::endl;
	
}
void	ncaa::rigid_static_plane::render( jess::shared_ptr<npr::base> rnd )
{
	//jess::clog << NEB_FUNCSIG << std::endl;
	
}
void	ncaa::rigid_static_plane::step( FLOAT dt )
{
	//jess::clog << NEB_FUNCSIG << std::endl;
	
}






void	ncaa::rigid_static_plane::create_shapes()
{
	jess::clog << NEB_FUNCSIG << std::endl;
	
	plane_ = create_plane();
}










