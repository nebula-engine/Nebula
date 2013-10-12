#include <nebula/platform/renderer/base.hpp>

#include <nebula/content/actor/admin/controller.hpp>

#include <nebula/content/actor/renderer/controller.hpp>

n34300::controller::controller()
{
}
n34300::controller::~controller()
{
}
void	n34300::controller::init( jess::shared_ptr<n34100::base> parent )
{
	jess::clog << NEB_FUNCSIG << std::endl;
	
	n34300::base::init( parent );

	
}
void	n34300::controller::shutdown()
{
	
}
void	n34300::controller::update()
{
	
}
void	n34300::controller::render( jess::shared_ptr<n23000::base> rnd )
{
	jess::shared_ptr<n34100::controller> parent = std::dynamic_pointer_cast<n34100::controller>( parent_.lock() );

	rnd->look_at( parent->pos_, parent->pos_ + parent->look_, parent->up_ );
}
void	n34300::controller::step( float dt )
{
	
}
void	n34300::controller::create_shapes()
{

}



























