#include <jess/scoped_ostream.hpp>

#include <nebula/platform/window/base.hpp>
#include <nebula/content/actor/admin/controller.hpp>

#include <nebula/content/actor/control/controller/default_control.hpp>

n34000::control::controller::default_control::default_control( jess::shared_ptr<n34100::controller::base> parent ):
	n34000::control::controller::base( parent )
{

}
n34000::control::controller::default_control::~default_control()
{

}
void				n34000::control::controller::default_control::init()
{
	float s = 1;
	float d = 0.707;

	s *= 1.5;
	d *= 1.5;

	head_[0] = physx::PxVec3(  0, 0, -s );
	head_[1] = physx::PxVec3(  d, 0, -d );
	head_[2] = physx::PxVec3(  s, 0,  0 );
	head_[3] = physx::PxVec3(  d, 0,  d );
	head_[4] = physx::PxVec3(  0, 0,  s );
	head_[5] = physx::PxVec3( -d, 0,  d );
	head_[6] = physx::PxVec3( -s, 0,  0 );
	head_[7] = physx::PxVec3( -d, 0, -d );
	
	head_flag_[n34000::control::controller::base::flag::eNORTH								] = 0;
	head_flag_[n34000::control::controller::base::flag::eNORTH	|	n34000::control::controller::base::flag::eEAST	] = 1;
	head_flag_[								n34000::control::controller::base::flag::eEAST	] = 2;
	head_flag_[n34000::control::controller::base::flag::eSOUTH	|	n34000::control::controller::base::flag::eEAST	] = 3;
	head_flag_[n34000::control::controller::base::flag::eSOUTH								] = 4;
	head_flag_[n34000::control::controller::base::flag::eSOUTH	|	n34000::control::controller::base::flag::eWEST	] = 5;
	head_flag_[								n34000::control::controller::base::flag::eWEST	] = 6;
	head_flag_[n34000::control::controller::base::flag::eNORTH	|	n34000::control::controller::base::flag::eWEST	] = 7;

}
void				n34000::control::controller::default_control::connect_to_window( jess::shared_ptr<n22000::base> window )
{

	// set signal handlers
	window->sig_pointer_motion_.connect
		(
		 std::bind
		 (
		  &n34000::control::controller::default_control::on_pointer_motion,
		  this,
		  std::placeholders::_1,
		  std::placeholders::_2
		 )
		);

	window->sig_key_down_.connect
		(
		 std::bind
		 (
		  &n34000::control::controller::default_control::on_key_down,
		  this,
		  std::placeholders::_1,
		  std::placeholders::_2
		 )
		);

	window->sig_key_up_.connect
		(
		 std::bind
		 (
		  &n34000::control::controller::default_control::on_key_up,
		  this,
		  std::placeholders::_1,
		  std::placeholders::_2
		 )
		);
}
bool			n34000::control::controller::default_control::is_valid()
{
	return true;
}
physx::PxVec3		n34000::control::controller::default_control::move()
{
	jess::scoped_ostream sos( &jess::clog, NEB_FUNCSIG );

	jess::shared_ptr<n34100::controller::base> parent = std::dynamic_pointer_cast<n34100::controller::base>(parent_.lock());
	
	/** \todo
	 * add gravity
	 * make \a head and \a m a static member variable or at least a member variables
	 */
	
	physx::PxVec3 mov(0,0,0);
	
	// ignore all other flags
	int f = parent->flag_ & (
			n34000::control::controller::base::flag::eNORTH |
			n34000::control::controller::base::flag::eSOUTH |
			n34000::control::controller::base::flag::eEAST |
			n34000::control::controller::base::flag::eWEST );
	
	// find vector for move flag
	auto it = head_flag_.find( f );

	if ( it != head_flag_.end() )
	{
		mov = head_[it->second];
	}
	
	jess::clog << "mov=" << mov.x << mov.y << mov.z << std::endl;
	
	return mov;
}
bool			n34000::control::controller::default_control::on_key_down( int k, int w )
{
	jess::scoped_ostream( &jess::clog, NEB_FUNCSIG );

	// set flag
	UINT f = key_flag_[k];
	flag_ |= f;

	// trigger event
	int evnt = key_down_event_[k];
	process_event(evnt);

	return true;

}
bool			n34000::control::controller::default_control::on_key_up( int k, int w )
{

	jess::scoped_ostream( &jess::clog, NEB_FUNCSIG );
	
	// unset flag
	flag_ &= ~( key_flag_[k] );
	
	// trigger event
	process_event( key_up_event_[k] );

	return true;

}
bool			n34000::control::controller::default_control::on_pointer_motion( int x, int y )
{
	jess::scoped_ostream( &jess::clog, NEB_FUNCSIG );

	jess::shared_ptr<n34100::controller::base> parent = std::dynamic_pointer_cast<n34100::controller::base>(parent_.lock());

	parent->yaw_ -= x * 0.001;
	parent->pitch_ -= y * 0.001;

	return true;
}



