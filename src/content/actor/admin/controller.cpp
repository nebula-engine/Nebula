#include <nebula/define.hpp>

#include <nebula/utilities/free.hpp>

#include <nebula/platform/renderer/base.hpp>
#include <nebula/platform/key.hpp>
#include <nebula/platform/window/base.hpp>

#include <nebula/content/actor/physics/controller.hpp>
#include <nebula/content/actor/renderer/controller.hpp>

#include <nebula/content/actor/admin/controller.hpp>

n34100::controller::controller( jess::shared_ptr<n32100::base> parent ):
	base( parent )
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
n34100::controller::~controller()
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
void	n34100::controller::init()
{
	jess::clog << NEB_FUNCSIG << std::endl;

	// parent
	n34100::base::init();

	flag_ = 0;

	yaw_ = 0;
	pitch_ = 0;

	pos_ = physx::PxVec3(0,0,2);

	key_flag_[nebula::platform::key::w] = flag::eNORTH;
	key_flag_[nebula::platform::key::s] = flag::eSOUTH;
	key_flag_[nebula::platform::key::a] = flag::eWEST;
	key_flag_[nebula::platform::key::d] = flag::eEAST;

	key_down_event_[nebula::platform::key::r] = event::eRESET_VIEW_ANGLES;

	// renderer
	renderer_.reset( new n34300::controller );
	renderer_->init( shared_from_this() );	
}
void	n34100::controller::shutdown()
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
void	n34100::controller::update()
{
	n34100::base::update();
}
void	n34100::controller::step( float dt )
{
	n34100::base::step( dt );
}
void	n34100::controller::render( jess::shared_ptr<n23000::base> rnd )
{
}
void	n34100::controller::create_shapes()
{

}
void	n34100::controller::look_at( jess::shared_ptr<n23000::base> rnd )
{
	jess::clog << NEB_FUNCSIG << std::endl;

	physx::PxQuat rot( yaw_, physx::PxVec3(0,1,0) );

	rot *= physx::PxQuat( pitch_ , physx::PxVec3(1,0,0) );

	up_ = physx::PxVec3(0,1,0);
	look_ = physx::PxVec3(0,0,-1);

	up_ = rot.rotate( up_ );
	look_ = rot.rotate( look_ );

	rnd->look_at( pos_, pos_ + look_, up_ );
}
void	n34100::controller::process_event( int evnt )
{
	switch ( evnt )
	{
		case event::eRESET_VIEW_ANGLES:
			printf("reset viewing angles\n");
			yaw_ = 0;
			pitch_ = 0;
			break;
	}
}
bool	n34100::controller::handle_key_up(int k, int window_no)
{

	jess::clog << NEB_FUNCSIG << std::endl;

	// unset flag
	UINT f = key_flag_[k];
	flag_ &= ~( f );

	// trigger event
	int evnt = key_up_event_[k];
	process_event(evnt);

	return true;
}
bool	n34100::controller::handle_key_down(int k, int window_no)
{

	jess::clog << NEB_FUNCSIG << std::endl;

	// set flag
	UINT f = key_flag_[k];
	flag_ |= f;

	// trigger event
	int evnt = key_down_event_[k];
	process_event(evnt);

	return true;
}
bool	n34100::controller::handle_pointer_motion( int x, int y )
{
	jess::clog << NEB_FUNCSIG << std::endl;

	yaw_ -= x * 0.001;
	pitch_ -= y * 0.001;

	return true;
}

























