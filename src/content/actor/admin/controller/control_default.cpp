#include <nebula/content/actor/admin/controller/control_default.hpp>

control( jess::shared_ptr<n34100::controller> )
{

}
virtual ~control()
{

}
virtual void			init()
{
	float s = 1;
	float d = 0.707;

	s *= 1.5;
	d *= 1.5;

	head[0] = physx::PxVec3(  0, 0, -s );
	head[1] = physx::PxVec3(  d, 0, -d );
	head[2] = physx::PxVec3(  s, 0,  0 );
	head[3] = physx::PxVec3(  d, 0,  d );
	head[4] = physx::PxVec3(  0, 0,  s );
	head[5] = physx::PxVec3( -d, 0,  d );
	head[6] = physx::PxVec3( -s, 0,  0 );
	head[7] = physx::PxVec3( -d, 0, -d );

	m[n34100::controller::flag::eNORTH						] = 0;
	m[n34100::controller::flag::eNORTH	|	n34100::controller::flag::eEAST	] = 1;
	m[						n34100::controller::flag::eEAST	] = 2;
	m[n34100::controller::flag::eSOUTH	|	n34100::controller::flag::eEAST	] = 3;
	m[n34100::controller::flag::eSOUTH						] = 4;
	m[n34100::controller::flag::eSOUTH	|	n34100::controller::flag::eWEST	] = 5;
	m[						n34100::controller::flag::eWEST	] = 6;
	m[n34100::controller::flag::eNORTH	|	n34100::controller::flag::eWEST	] = 7;



}
virtual bool			is_valid()
{
	return true;
}
virtual physx::PxVec3		move()
{
	jess::scoped_ostream sos( &jess::clog, NEB_FUNCSIG );

	jess::shared_ptr<n34100::controller> parent = std::dynamic_pointer_cast<n34100::controller>(parent_.lock());
	
	/** \todo
	 * add gravity
	 * make \a head and \a m a static member variable or at least a member variables
	 */
	
	physx::PxVec3 mov(0,0,0);
	
	// ignore all other flags
	int f = parent->flag_ & (
			n34100::controller::flag::eNORTH |
			n34100::controller::flag::eSOUTH |
			n34100::controller::flag::eEAST |
			n34100::controller::flag::eWEST );
	
	// find vector for move flag
	auto it = m.find( f );

	if ( it != m.end() )
	{
		mov = head[it->second];
	}
	
	jess::clog << "mov=" << mov << std::endl;
	
	return mov;
}
virtual bool			on_key_down( int k, int w )
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
virtual bool			on_key_up( int k, int w )
{

	jess::scoped_ostream( &jess::clog, NEB_FUNCSIG );
	
	// unset flag
	flag_ &= ~( key_flag_[k] );
	
	// trigger event
	process_event( key_up_event_[k] );

	return true;

}
virtual bool			on_pointer_motion( int x, int y )
{
	jess::scoped_ostream( &jess::clog, NEB_FUNCSIG );

	yaw_ -= x * 0.001;
	pitch_ -= y * 0.001;

	return true;
}



