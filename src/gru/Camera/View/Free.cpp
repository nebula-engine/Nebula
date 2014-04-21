
#include <gru/config.hpp>
#include <gru/window/window.hpp>
#include <gru/Camera/View/Free.hpp>

glutpp::Camera::View::Free::Free():
	eye_(0.0f, 0.0f, 5.0f, 0.0f),
	center_(0.0f,0.0f,0.0f),
	up_(0.0f,1.0f,0.0f)
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

	head_flag_[glutpp::Camera::View::Base::Flag::E::NORTH								] = 0;
	head_flag_[glutpp::Camera::View::Base::Flag::E::NORTH	|	glutpp::Camera::View::Base::Flag::E::EAST	] = 1;
	head_flag_[							glutpp::Camera::View::Base::Flag::E::EAST	] = 2;
	head_flag_[glutpp::Camera::View::Base::Flag::E::SOUTH	|	glutpp::Camera::View::Base::Flag::E::EAST	] = 3;
	head_flag_[glutpp::Camera::View::Base::Flag::E::SOUTH								] = 4;
	head_flag_[glutpp::Camera::View::Base::Flag::E::SOUTH	|	glutpp::Camera::View::Base::Flag::E::WEST	] = 5;
	head_flag_[							glutpp::Camera::View::Base::Flag::E::WEST	] = 6;
	head_flag_[glutpp::Camera::View::Base::Flag::E::NORTH	|	glutpp::Camera::View::Base::Flag::E::WEST	] = 7;


}
void	glutpp::Camera::View::Free::init(glutpp::window::window_s window)
{
	window_ = window;
/*
	vec_x_.push_back(
			window_->map_sig_key_down_['d'].connect(
				std::bind(&glutpp::Camera::View::Free::callback_x_, this, 0, 1.0)));

	vec_x_.push_back(
			window_->map_sig_key_up_['d'].connect(
				std::bind(&glutpp::Camera::View::Free::callback_x_, this, 0, 0.0)));

	vec_x_.push_back(
			window_->map_sig_key_down_['a'].connect(
				std::bind(&glutpp::Camera::View::Free::callback_x_, this, 1, -1.0)));

	vec_x_.push_back(
			window_->map_sig_key_up_['a'].connect(
				std::bind(&glutpp::Camera::View::Free::callback_x_, this, 1, 0.0)));

	vec_y_.push_back(
			window_->map_sig_key_down_['e'].connect(
				std::bind(&glutpp::Camera::View::Free::callback_y_, this, 0, 1.0)));

	vec_y_.push_back(
			window_->map_sig_key_up_['e'].connect(
				std::bind(&glutpp::Camera::View::Free::callback_y_, this, 0, 0.0)));

	vec_y_.push_back(
			window_->map_sig_key_down_['c'].connect(
				std::bind(&glutpp::Camera::View::Free::callback_y_, this, 1, -1.0)));

	vec_y_.push_back(
			window_->map_sig_key_up_['c'].connect(
				std::bind(&glutpp::Camera::View::Free::callback_y_, this, 1, 0.0)));

	vec_z_.push_back(
			window_->map_sig_key_down_['w'].connect(
				std::bind(&glutpp::Camera::View::Free::callback_z_, this, 0, -1.0)));

	vec_z_.push_back(
			window_->map_sig_key_up_['w'].connect(
				std::bind(&glutpp::Camera::View::Free::callback_z_, this, 0, 0.0)));

	vec_z_.push_back(
			window_->map_sig_key_down_['s'].connect(
				std::bind(&glutpp::Camera::View::Free::callback_z_, this, 1, 1.0)));

	vec_z_.push_back(
			window_->map_sig_key_up_['s'].connect(
				std::bind(&glutpp::Camera::View::Free::callback_z_, this, 1, 0.0)));
*/

}
void	glutpp::Camera::View::Free::Step(double time) {
	double dt = time - last_; last_ = time;

	// look vector
	math::vec3<double> look = center_ - eye_;

	// project to xz-plane
	look.y() = 0.0;
	look.Normalize();

	math::vec3<double> x(1,0,0);
	math::vec3<double> y(0,1,0);
	math::vec3<double> z(0,0,-1);

	math::vec3<double> c = z.cross(look);

	float yaw = asin(c.magnitude());

	float d = y.dot(c);
	float e = z.dot(look);

	if(e < 0) yaw = M_PI - yaw;


	yaw *= (d > 0) ? 1.0 : -1.0;


	printf("yaw = %f\n",yaw);

	// rotate velocity by camera yaw
	math::quat q(yaw,y);
	
	
	math::vec3<double> v = v0_ + v1_;
	v *= dt;
	v *= 4.0;

	v = q.rotate(v);
	
	eye_ += math::vec4(v, 0.0f);
}

/*
neb::camera::camera::camera():
	pitch_(0.0f),
	yaw_(0.0f),
	v_pitch_(0.0f),
	v_yaw_(0.0f),
	eye_( physx::PxVec3( 0.0f, 0.0f, 0.0f ) )
{

}
void	neb::camera::camera::Connect()
{
	ev_mouse = JSL::master.find_event_device(	{LOGITECH,	MOUSE});
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
	}
}
void neb::camera::camera::Step(float dt)
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
physx::PxVec3 neb::camera::camera::Move()
{
	//printf("%s\n", __FUNCTION__);

	physx::PxVec3 mov = physx::PxVec3(0,0,-1) * north_ + physx::PxVec3(1,0,0) * east_;

	return mov;
	
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
	
	return mov;
}
*/
math::mat44 glutpp::Camera::View::Free::view() {
	//printf("%s\n", __FUNCTION__);

	math::vec3<double> up(0,1,0);
	math::vec3<double> look(0,0,-1);
	
	
	math::quat rot( yaw_, math::vec3<double>(0,1,0));

	rot *= math::quat( pitch_ , math::vec3<double>(1,0,0) );


	up = rot.rotate( up );
	look = rot.rotate( look );
	
	math::vec3<double> eye(eye_.x, eye_.y, eye_.z);
	
	math::vec3<double> center = eye + look;

	math::mat44 ret = math::lookat(eye_, center, up);

	//		eye_.x, eye_.y, eye_.z,
	//		center.x, center.y, center.z,
	//		up.x, up.y, up.z );
	
	return ret;
}
/*
int	neb::camera::camera::FirstOrderDeltaPitchRel(int d)
{
	//printf("%s\n", __FUNCTION__);

	pitch_ -= (float)d * 0.001;

	return 1;
}
int	neb::camera::camera::FirstOrderDeltaYawRel(int d)
{
	//printf("%s\n", __FUNCTION__);

	yaw_ -= (float)d * 0.001;

	return 1;
}
int neb::camera::camera::FirstOrderDeltaPitchAbs(float d)
{
	printf("%s %f\n", __FUNCTION__, d);

	d = ((d > 0.1 || d < -0.1) ? d : 0.0f);

	v_pitch_ = (float)d * -1.0;

	return 1;
}
int neb::camera::camera::FirstOrderDeltaYawAbs(float d)
{
	printf("%s %f\n", __FUNCTION__, d);

	d = ((d > 0.1 || d < -0.1) ? d : 0.0f);

	v_yaw_ = (float)d * -1.0;

	return 1;
}
*/






