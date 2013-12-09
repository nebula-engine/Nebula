
#include <assert.h>

#include <JSL/Master.h>

#include <GRU/Window.h>

#include <NEB/Scene.h>
#include <NEB/View.h>
#include <NEB/Camera.h>

NEB::Camera::Camera():
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
	   key_flag_[ KEY_W ] = NEB::Camera::flag::NORTH;
	   key_flag_[ KEY_S ] = NEB::Camera::flag::SOUTH;
	   key_flag_[ KEY_D ] = NEB::Camera::flag::EAST;
	   key_flag_[ KEY_A ] = NEB::Camera::flag::WEST;
	 */	

	head_[0] = physx::PxVec3(  0, 0, -s );
	head_[1] = physx::PxVec3(  d, 0, -d );
	head_[2] = physx::PxVec3(  s, 0,  0 );
	head_[3] = physx::PxVec3(  d, 0,  d );
	head_[4] = physx::PxVec3(  0, 0,  s );
	head_[5] = physx::PxVec3( -d, 0,  d );
	head_[6] = physx::PxVec3( -s, 0,  0 );
	head_[7] = physx::PxVec3( -d, 0, -d );

	head_flag_[NEB::Camera::flag::NORTH					] = 0;
	head_flag_[NEB::Camera::flag::NORTH	|	NEB::Camera::flag::EAST	] = 1;
	head_flag_[					NEB::Camera::flag::EAST	] = 2;
	head_flag_[NEB::Camera::flag::SOUTH	|	NEB::Camera::flag::EAST	] = 3;
	head_flag_[NEB::Camera::flag::SOUTH					] = 4;
	head_flag_[NEB::Camera::flag::SOUTH	|	NEB::Camera::flag::WEST	] = 5;
	head_flag_[					NEB::Camera::flag::WEST	] = 6;
	head_flag_[NEB::Camera::flag::NORTH	|	NEB::Camera::flag::WEST	] = 7;

}
void	NEB::Camera::Connect()
{
	ev_mouse = JSL::master.find_event_device(	{LOGITECH,	MOUSE});
	ev_keyboard = JSL::master.find_event_device(	{LOGITECH,	KEYBOARD});
	ev_gamepad = JSL::master.find_event_device(	{XBOX,		CONTROLLER});

	if(ev_gamepad)
	{
		ev_gamepad->map_sig_abs_[ABS_RX].connect(std::bind( &NEB::Camera::FirstOrderDeltaYawAbs, this, std::placeholders::_1 ) );
		ev_gamepad->map_sig_abs_[ABS_RY].connect(std::bind( &NEB::Camera::FirstOrderDeltaPitchAbs, this, std::placeholders::_1 ) );

		ev_gamepad->map_sig_abs_[ABS_Y].connect(std::bind( &NEB::Camera::HandleAbsNorth, this, std::placeholders::_1 ) );
		ev_gamepad->map_sig_abs_[ABS_X].connect(std::bind( &NEB::Camera::HandleAbsEast, this, std::placeholders::_1 ) );

		ev_gamepad->map_sig_key_[BTN_A].connect(std::bind(&NEB::Camera::handle_delete_scene, this, std::placeholders::_1));

		fprintf(stderr, "Camera: gamepad");
	}
	else if(ev_mouse && ev_keyboard)
	{
		ev_mouse->map_sig_rel_[REL_X].connect(	std::bind( &NEB::Camera::FirstOrderDeltaYawRel, this, std::placeholders::_1 ) );
		ev_mouse->map_sig_rel_[REL_Y].connect(	std::bind( &NEB::Camera::FirstOrderDeltaPitchRel, this, std::placeholders::_1 ) );

		ev_keyboard->map_sig_key_[KEY_W].connect(std::bind( &NEB::Camera::HandleKeyNorth, this, std::placeholders::_1 ) );
		ev_keyboard->map_sig_key_[KEY_S].connect(std::bind( &NEB::Camera::HandleKeySouth, this, std::placeholders::_1 ) );
		ev_keyboard->map_sig_key_[KEY_D].connect(std::bind( &NEB::Camera::HandleKeyEast, this, std::placeholders::_1 ) );
		ev_keyboard->map_sig_key_[KEY_A].connect(std::bind( &NEB::Camera::HandleKeyWest, this, std::placeholders::_1 ) );

		ev_gamepad->map_sig_key_[KEY_S].connect(std::bind(&NEB::Camera::handle_delete_scene, this, std::placeholders::_1));


		fprintf(stderr, "Camera: mouse and keyboard");

	}
	else
	{
		fprintf(stderr, "Camera: no input devices");
	}
}
void	NEB::Camera::SetWindow( GRU::Window* window )
{
	assert( window );

	window->CallBackDisplay_ = std::bind( &NEB::Camera::Display, this );
	window->CallBackIdle_ = std::bind( &NEB::Camera::Display, this );
}
void	NEB::Camera::Display()
{
	Step(1.0f/60.0f);

	//Look();


	if( view_ )
	{
		view_->Display();
	}

}
void NEB::Camera::Step(float dt)
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
physx::PxVec3 NEB::Camera::Move()
{
	//printf("%s\n", __FUNCTION__);

	physx::PxVec3 mov = physx::PxVec3(0,0,-1) * north_ + physx::PxVec3(1,0,0) * east_;

	return mov;
	/*
	   physx::PxVec3 mov(0,0,0);

	// ignore all other flags
	int f = flag_ & (
	NEB::Camera::flag::NORTH |
	NEB::Camera::flag::SOUTH |
	NEB::Camera::flag::EAST |
	NEB::Camera::flag::WEST );

	// find vector for move flag
	auto it = head_flag_.find( f );

	if ( it != head_flag_.end() )
	{
	mov = head_[it->second];
	}
	 */
	return mov;
}
void NEB::Camera::Look()
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
void	NEB::Camera::delete_scene()
{
	view_->delete_scene();
}
int	NEB::Camera::FirstOrderDeltaPitchRel(int d)
{
	//printf("%s\n", __FUNCTION__);

	pitch_ -= (float)d * 0.001;

	return 1;
}
int	NEB::Camera::FirstOrderDeltaYawRel(int d)
{
	//printf("%s\n", __FUNCTION__);

	yaw_ -= (float)d * 0.001;

	return 1;
}
int NEB::Camera::FirstOrderDeltaPitchAbs(float d)
{
	printf("%s %f\n", __FUNCTION__, d);

	d = ((d > 0.1 || d < -0.1) ? d : 0.0f);

	v_pitch_ = (float)d * -1.0;

	return 1;
}
int NEB::Camera::FirstOrderDeltaYawAbs(float d)
{
	printf("%s %f\n", __FUNCTION__, d);

	d = ((d > 0.1 || d < -0.1) ? d : 0.0f);

	v_yaw_ = (float)d * -1.0;

	return 1;
}
int NEB::Camera::HandleAbsNorth(float d)
{
	d = ((d > 0.1 || d < -0.1) ? d : 0.0f);

	north_ = -1.0 * d;

	return 1;
}
int NEB::Camera::HandleAbsEast(float d)
{
	d = ((d > 0.1 || d < -0.1) ? d : 0.0f);

	east_ = 1.0 * d;

	return 1;
}
int	NEB::Camera::handle_delete_scene(__s32)
{
	delete_scene();

	return 1;
}
int NEB::Camera::HandleKeyNorth(__s32 value)
{
	if( value == 0 )
	{
		flag_ &= ~( NEB::Camera::flag::NORTH );
	}
	else if( value == 1 )
	{
		flag_ |= NEB::Camera::flag::NORTH;
	}

	return 1;
}
int NEB::Camera::HandleKeySouth(__s32 value)
{
	if( value == 0 )
	{
		flag_ &= ~( NEB::Camera::flag::SOUTH );
	}
	else if( value == 1 )
	{
		flag_ |= NEB::Camera::flag::SOUTH;
	}

	return 1;
}
int NEB::Camera::HandleKeyEast(__s32 value)
{
	if( value == 0 )
	{
		flag_ &= ~( NEB::Camera::flag::EAST );
	}
	else if( value == 1 )
	{
		flag_ |= NEB::Camera::flag::EAST;
	}

	return 1;
}
int NEB::Camera::HandleKeyWest(__s32 value)
{
	if( value == 0 )
	{
		flag_ &= ~( NEB::Camera::flag::WEST );
	}
	else if( value == 1 )
	{
		flag_ |= NEB::Camera::flag::WEST;
	}

	return 1;
}


