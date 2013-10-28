#include <nebula/content/actor/renderer/rigid_static_plane.hpp>
#include <nebula/content/shape/admin/plane.hpp>

#include <nebula/content/actor/admin/rigid_static_plane.hpp>

n34100::rigid_static_plane::rigid_static_plane( std::shared_ptr<n32100::base> parent ):
	rigid_static( parent )
{
}
n34100::rigid_static_plane::~rigid_static_plane()
{
}
void	n34100::rigid_static_plane::init()
{
	jess::clog << NEB_FUNCSIG << std::endl;

	n34100::rigid_static::init();
	
	renderer_.reset( new n34300::rigid_static_plane( shared_from_this() ) );
	renderer_->init();
}
void	n34100::rigid_static_plane::shutdown()
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
void	n34100::rigid_static_plane::update()
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
void	n34100::rigid_static_plane::render( std::shared_ptr<n23000::base> rnd )
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
void	n34100::rigid_static_plane::step( float dt )
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
void	n34100::rigid_static_plane::create_shapes()
{
	jess::clog << NEB_FUNCSIG << std::endl;

	plane_ = create_plane();
}


