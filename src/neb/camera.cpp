
#include <assert.h>

//#include <JSL/Master.h>

#include <glutpp/window.h>

#include <neb/scene.h>
#include <neb/view.h>
#include <neb/camera.h>

neb::camera::camera():
	pitch_(0.0f),
	yaw_(0.0f),
	v_pitch_(0.0f),
	v_yaw_(0.0f),
	eye_( physx::PxVec3( 0.0f, 0.0f, 0.0f ) )
{
	float s = 1;
	float d = 0.707;

	s *= 1.5;
	d *= 1.5;
	/*
	   key_flag_[ KEY_W ] = NEB::camera::flag::NORTH;
	   key_flag_[ KEY_S ] = NEB::camera::flag::SOUTH;
	   key_flag_[ KEY_D ] = NEB::camera::flag::EAST;
	   key_flag_[ KEY_A ] = NEB::camera::flag::WEST;
	 */	

	head_[0] = physx::PxVec3(  0, 0, -s );
	head_[1] = physx::PxVec3(  d, 0, -d );
	head_[2] = physx::PxVec3(  s, 0,  0 );
	head_[3] = physx::PxVec3(  d, 0,  d );
	head_[4] = physx::PxVec3(  0, 0,  s );
	head_[5] = physx::PxVec3( -d, 0,  d );
	head_[6] = physx::PxVec3( -s, 0,  0 );
	head_[7] = physx::PxVec3( -d, 0, -d );

	head_flag_[neb::camera::flag::NORTH					] = 0;
	head_flag_[neb::camera::flag::NORTH	|	neb::camera::flag::EAST	] = 1;
	head_flag_[					neb::camera::flag::EAST	] = 2;
	head_flag_[neb::camera::flag::SOUTH	|	neb::camera::flag::EAST	] = 3;
	head_flag_[neb::camera::flag::SOUTH					] = 4;
	head_flag_[neb::camera::flag::SOUTH	|	neb::camera::flag::WEST	] = 5;
	head_flag_[					neb::camera::flag::WEST	] = 6;
	head_flag_[neb::camera::flag::NORTH	|	neb::camera::flag::WEST	] = 7;

}
void	neb::camera::Connect()
{
/*	ev_mouse = JSL::master.find_event_device(	{LOGITECH,	MOUSE});
	ev_keyboard = JSL::master.find_event_device(	{LOGITECH,	KEYBOARD});
	ev_gamepad = JSL::master.find_event_device(	{XBOX,		CONTROLLER});

	if(ev_gamepad)
	{
		ev_gamepad->map_sig_abs_[ABS_RX].connect(std::bind( &neb::camera::FirstOrderDeltaYawAbs, this, std::placeholders::_1 ) );
		ev_gamepad->map_sig_abs_[ABS_RY].connect(std::bind( &neb::camera::FirstOrderDeltaPitchAbs, this, std::placeholders::_1 ) );

		ev_gamepad->map_sig_abs_[ABS_Y].connect(std::bind( &neb::camera::HandleAbsNorth, this, std::placeholders::_1 ) );
		ev_gamepad->map_sig_abs_[ABS_X].connect(std::bind( &neb::camera::HandleAbsEast, this, std::placeholders::_1 ) );

		ev_gamepad->map_sig_key_[BTN_A].connect(std::bind(&neb::camera::handle_delete_scene, this, std::placeholders::_1));

		fprintf(stderr, "camera: gamepad");
	}
	else if(ev_mouse && ev_keyboard)
	{
		ev_mouse->map_sig_rel_[REL_X].connect(	std::bind( &neb::camera::FirstOrderDeltaYawRel, this, std::placeholders::_1 ) );
		ev_mouse->map_sig_rel_[REL_Y].connect(	std::bind( &neb::camera::FirstOrderDeltaPitchRel, this, std::placeholders::_1 ) );

		ev_keyboard->map_sig_key_[KEY_W].connect(std::bind( &neb::camera::HandleKeyNorth, this, std::placeholders::_1 ) );
		ev_keyboard->map_sig_key_[KEY_S].connect(std::bind( &neb::camera::HandleKeySouth, this, std::placeholders::_1 ) );
		ev_keyboard->map_sig_key_[KEY_D].connect(std::bind( &neb::camera::HandleKeyEast, this, std::placeholders::_1 ) );
		ev_keyboard->map_sig_key_[KEY_A].connect(std::bind( &neb::camera::HandleKeyWest, this, std::placeholders::_1 ) );

		ev_gamepad->map_sig_key_[KEY_S].connect(std::bind(&neb::camera::handle_delete_scene, this, std::placeholders::_1));


		fprintf(stderr, "camera: mouse and keyboard");

	}
	else
	{
		fprintf(stderr, "camera: no input devices");
	}*/
}
void	neb::camera::SetWindow( glutpp::window* window )
{
	assert( window );
/*
	window->CallBackDisplay_ = std::bind( &neb::camera::Display, this );
	window->CallBackIdle_ = std::bind( &neb::camera::Display, this );
*/
}
void	neb::camera::Display()
{
	Step(1.0f/60.0f);

	//Look();


	if( view_ )
	{
		view_->Display();
	}

}
void neb::camera::Step(float dt)
{
	//printf("%s\n", __FUNCTION__);

	physx::PxVec3 mov = Move();

	physx::PxQuat rot( yaw_, physx::PxVec3(0,1,0) );

	mov = rot.rotate(mov);

	eye_ += mov * dt;

	// pitch
	pitch_ += v_pitch_ * dt;

	// yaw
	yaw_ += v_yaw_ * dt;
}
physx::PxVec3 neb::camera::Move()
{
	//printf("%s\n", __FUNCTION__);

	physx::PxVec3 mov = physx::PxVec3(0,0,-1) * north_ + physx::PxVec3(1,0,0) * east_;

	return mov;
	/*
	   physx::PxVec3 mov(0,0,0);

	// ignore all other flags
	int f = flag_ & (
	neb::camera::flag::NORTH |
	neb::camera::flag::SOUTH |
	neb::camera::flag::EAST |
	neb::camera::flag::WEST );

	// find vector for move flag
	auto it = head_flag_.find( f );

	if ( it != head_flag_.end() )
	{
	mov = head_[it->second];
	}
	 */
	return mov;
}
void neb::camera::Look()
{
	//printf("%s\n", __FUNCTION__);

	physx::PxVec3 up(  0,1,0);
	physx::PxVec3 look(0,0,-1);


	physx::PxQuat rot( yaw_, physx::PxVec3(0,1,0) );

	rot *= physx::PxQuat( pitch_ , physx::PxVec3(1,0,0) );


	up = rot.rotate( up );
	look = rot.rotate( look );

	physx::PxVec3 center = eye_ + look;

	gluLookAt(
			eye_.x, eye_.y, eye_.z,
			center.x, center.y, center.z,
			up.x, up.y, up.z );

}
void	neb::camera::delete_scene()
{
	view_->delete_scene();
}
int	neb::camera::FirstOrderDeltaPitchRel(int d)
{
	//printf("%s\n", __FUNCTION__);

	pitch_ -= (float)d * 0.001;

	return 1;
}
int	neb::camera::FirstOrderDeltaYawRel(int d)
{
	//printf("%s\n", __FUNCTION__);

	yaw_ -= (float)d * 0.001;

	return 1;
}
int neb::camera::FirstOrderDeltaPitchAbs(float d)
{
	printf("%s %f\n", __FUNCTION__, d);

	d = ((d > 0.1 || d < -0.1) ? d : 0.0f);

	v_pitch_ = (float)d * -1.0;

	return 1;
}
int neb::camera::FirstOrderDeltaYawAbs(float d)
{
	printf("%s %f\n", __FUNCTION__, d);

	d = ((d > 0.1 || d < -0.1) ? d : 0.0f);

	v_yaw_ = (float)d * -1.0;

	return 1;
}
int neb::camera::HandleAbsNorth(float d)
{
	d = ((d > 0.1 || d < -0.1) ? d : 0.0f);

	north_ = -1.0 * d;

	return 1;
}
int neb::camera::HandleAbsEast(float d)
{
	d = ((d > 0.1 || d < -0.1) ? d : 0.0f);

	east_ = 1.0 * d;

	return 1;
}
int	neb::camera::handle_delete_scene(int)
{
	delete_scene();

	return 1;
}
int neb::camera::HandleKeyNorth(int value)
{
	if( value == 0 )
	{
		flag_ &= ~( neb::camera::flag::NORTH );
	}
	else if( value == 1 )
	{
		flag_ |= neb::camera::flag::NORTH;
	}

	return 1;
}
int neb::camera::HandleKeySouth(int value)
{
	if( value == 0 )
	{
		flag_ &= ~( neb::camera::flag::SOUTH );
	}
	else if( value == 1 )
	{
		flag_ |= neb::camera::flag::SOUTH;
	}

	return 1;
}
int neb::camera::HandleKeyEast(int value)
{
	if( value == 0 )
	{
		flag_ &= ~( neb::camera::flag::EAST );
	}
	else if( value == 1 )
	{
		flag_ |= neb::camera::flag::EAST;
	}

	return 1;
}
int neb::camera::HandleKeyWest(int value)
{
	if( value == 0 )
	{
		flag_ &= ~( neb::camera::flag::WEST );
	}
	else if( value == 1 )
	{
		flag_ |= neb::camera::flag::WEST;
	}

	return 1;
}




