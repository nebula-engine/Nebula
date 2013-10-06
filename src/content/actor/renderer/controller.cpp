#include <nebula/platform/renderer/base.hpp>

#include <nebula/content/actor/admin/controller.hpp>

#include <nebula/content/actor/renderer/controller.hpp>

ncar::controller::controller()
{
}
ncar::controller::~controller()
{
}
void	ncar::controller::init( jess::shared_ptr<ncaa::base>& parent )
{
	jess::clog << NEB_FUNCSIG << std::endl;
	
	ncar::base::init( parent );

	
}
void	ncar::controller::shutdown()
{
	
}
void	ncar::controller::update()
{
	
}
void	ncar::controller::render( jess::shared_ptr<npr::base>& rnd )
{
	jess::shared_ptr<ncaa::controller> parent = std::dynamic_pointer_cast<ncaa::controller>( parent_.lock() );

	rnd->look_at( parent->pos_, parent->pos_ + parent->look_, parent->up_ );
}
void	ncar::controller::step( FLOAT dt )
{
	
}
void	ncar::controller::create_shapes()
{

}



























