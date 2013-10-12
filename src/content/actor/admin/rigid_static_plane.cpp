#include <nebula/content/actor/admin/rigid_static_plane.hpp>


		n34100::rigid_static_plane::rigid_static_plane() {
}
		n34100::rigid_static_plane::~rigid_static_plane() {
}




void	n34100::rigid_static_plane::init( jess::shared_ptr<n32100::base> parent )
{
	//jess::clog << NEB_FUNCSIG << std::endl;
	ncaa::rigid_static::init( parent );

	physics_.reset( new ncap::rigid_static_plane() );
	physics_->init( shared_from_this() );

	renderer_.reset( new ncar::rigid_static_plane );
	renderer_->init( shared_from_this() );
	
}
void	n34100::rigid_static_plane::shutdown() {
	//jess::clog << NEB_FUNCSIG << std::endl;
	
}
void	n34100::rigid_static_plane::update() {
	//jess::clog << NEB_FUNCSIG << std::endl;
	
}
void	n34100::rigid_static_plane::render( jess::shared_ptr<n23000::base> rnd )
{
	//jess::clog << NEB_FUNCSIG << std::endl;
	
}
void	n34100::rigid_static_plane::step( float dt )
{
	//jess::clog << NEB_FUNCSIG << std::endl;
	
}






void	n34100::rigid_static_plane::create_shapes()
{
	jess::clog << NEB_FUNCSIG << std::endl;
	
	plane_ = create_plane();
}










