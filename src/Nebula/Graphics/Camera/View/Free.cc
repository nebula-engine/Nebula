

#include <glm/gtc/matrix_transform.hpp>

#include <Galaxy-Log/log.hpp>

#include <Nebula/config.hh>
#include <Nebula/Graphics/Window/Base.hh>
#include <Nebula/Graphics/Camera/View/Free.hh>

neb::gfx::Camera::View::Free::Free(sp::shared_ptr<neb::gfx::Context::Base> parent):
	neb::gfx::Camera::View::Base(parent),
	pitch_(0),
	yaw_(0),
	eye_(0, 0, 0, 0),
	center_(0, 0, -1),
	up_(0, 1, 0)
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

	head_[0] = vec3(  0, 0, -s );
	head_[1] = vec3(  d, 0, -d );
	head_[2] = vec3(  s, 0,  0 );
	head_[3] = vec3(  d, 0,  d );
	head_[4] = vec3(  0, 0,  s );
	head_[5] = vec3( -d, 0,  d );
	head_[6] = vec3( -s, 0,  0 );
	head_[7] = vec3( -d, 0, -d );

	head_flag_[neb::gfx::Camera::View::Free::Flag::E::NORTH								] = 0;
	head_flag_[neb::gfx::Camera::View::Free::Flag::E::NORTH	|	neb::gfx::Camera::View::Free::Flag::E::EAST	] = 1;
	head_flag_[							neb::gfx::Camera::View::Free::Flag::E::EAST	] = 2;
	head_flag_[neb::gfx::Camera::View::Free::Flag::E::SOUTH	|	neb::gfx::Camera::View::Free::Flag::E::EAST	] = 3;
	head_flag_[neb::gfx::Camera::View::Free::Flag::E::SOUTH								] = 4;
	head_flag_[neb::gfx::Camera::View::Free::Flag::E::SOUTH	|	neb::gfx::Camera::View::Free::Flag::E::WEST	] = 5;
	head_flag_[							neb::gfx::Camera::View::Free::Flag::E::WEST	] = 6;
	head_flag_[neb::gfx::Camera::View::Free::Flag::E::NORTH	|	neb::gfx::Camera::View::Free::Flag::E::WEST	] = 7;


}
void	neb::gfx::Camera::View::Free::init() {
	/*
	   vec_x_.push_back(
	   window_->map_sig_key_down_['d'].connect(
	   std::bind(&neb::gfx::Camera::View::Free::callback_x_, this, 0, 1.0)));

	   vec_x_.push_back(
	   window_->map_sig_key_up_['d'].connect(
	   std::bind(&neb::gfx::Camera::View::Free::callback_x_, this, 0, 0.0)));

	   vec_x_.push_back(
	   window_->map_sig_key_down_['a'].connect(
	   std::bind(&neb::gfx::Camera::View::Free::callback_x_, this, 1, -1.0)));

	   vec_x_.push_back(
	   window_->map_sig_key_up_['a'].connect(
	   std::bind(&neb::gfx::Camera::View::Free::callback_x_, this, 1, 0.0)));

	   vec_y_.push_back(
	   window_->map_sig_key_down_['e'].connect(
	   std::bind(&neb::gfx::Camera::View::Free::callback_y_, this, 0, 1.0)));

	   vec_y_.push_back(
	   window_->map_sig_key_up_['e'].connect(
	   std::bind(&neb::gfx::Camera::View::Free::callback_y_, this, 0, 0.0)));

	   vec_y_.push_back(
	   window_->map_sig_key_down_['c'].connect(
	   std::bind(&neb::gfx::Camera::View::Free::callback_y_, this, 1, -1.0)));

	   vec_y_.push_back(
	   window_->map_sig_key_up_['c'].connect(
	   std::bind(&neb::gfx::Camera::View::Free::callback_y_, this, 1, 0.0)));

	   vec_z_.push_back(
	   window_->map_sig_key_down_['w'].connect(
	   std::bind(&neb::gfx::Camera::View::Free::callback_z_, this, 0, -1.0)));

	   vec_z_.push_back(
	   window_->map_sig_key_up_['w'].connect(
	   std::bind(&neb::gfx::Camera::View::Free::callback_z_, this, 0, 0.0)));

	   vec_z_.push_back(
	   window_->map_sig_key_down_['s'].connect(
	   std::bind(&neb::gfx::Camera::View::Free::callback_z_, this, 1, 1.0)));

	   vec_z_.push_back(
	   window_->map_sig_key_up_['s'].connect(
	   std::bind(&neb::gfx::Camera::View::Free::callback_z_, this, 1, 0.0)));
	 */

}
void		neb::gfx::Camera::View::Free::step(neb::core::TimeStep const & ts) {

	// look vector
	vec3 look = center_ - vec3(eye_);

	// project to xz-plane
	look.y = 0.0;
	glm::normalize(look);

	vec3 x(1,0,0);
	vec3 y(0,1,0);
	vec3 z(0,0,-1);

	vec3 c = glm::cross(z,look);

	float yaw = asin(glm::length(c));

	float d = glm::dot(y, c);
	float e = glm::dot(z, look);

	if(e < 0) yaw = M_PI - yaw;


	yaw *= (d > 0) ? 1.0 : -1.0;


	printf("yaw = %f\n",yaw);

	// rotate velocity by camera yaw
	quat q(yaw,y);


	vec3 v = v0_ + v1_;
	v *= ts.dt;
	v *= 4.0;

	v = q * v;

	eye_ += vec4(v, 0.0f);
}

/*
   neb::camera::camera::camera():
   pitch_(0.0f),
   yaw_(0.0f),
   v_pitch_(0.0f),
   v_yaw_(0.0f),
   eye_( vec3( 0.0f, 0.0f, 0.0f ) )
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

vec3 mov = Move();

physx::PxQuat rot( yaw_, vec3(0,1,0) );

mov = rot.rotate(mov);

eye_ += mov * dt;

// pitch
pitch_ += v_pitch_ * dt;

// yaw
yaw_ += v_yaw_ * dt;
}
vec3 neb::camera::camera::Move()
{
//printf("%s\n", __FUNCTION__);

vec3 mov = vec3(0,0,-1) * north_ + vec3(1,0,0) * east_;

return mov;

vec3 mov(0,0,0);

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
mat4		neb::gfx::Camera::View::Free::view() {
	printf("%s\n", __FUNCTION__);
	
	vec3 up(0,1,0);
	vec3 look(0,0,-1);


	quat rot( yaw_, vec3(0,1,0));

	rot = rot * quat( pitch_ , vec3(1,0,0) );

	up = rot * up;
	look = rot * look;

	vec3 eye(eye_);//.x(), eye_.y(), eye_.z());

	vec3 center = eye + look;

	mat4 ret = glm::lookAt(eye, center, up);

	BOOST_LOG_CHANNEL_SEV(lg, "neb gfx", debug) << ::std::setw(8) << "yaw" << ::std::setw(8) << yaw_;
	BOOST_LOG_CHANNEL_SEV(lg, "neb gfx", debug) << ::std::setw(8) << "pitch" << ::std::setw(8) << pitch_;
	BOOST_LOG_CHANNEL_SEV(lg, "neb gfx", debug) << ::std::setw(8) << "eye"
		<< ::std::setw(8) << eye[0]
		<< ::std::setw(8) << eye[1]
		<< ::std::setw(8) << eye[2];
	BOOST_LOG_CHANNEL_SEV(lg, "neb gfx", debug) << ::std::setw(8) << "center"
		<< ::std::setw(8) << center[0]
		<< ::std::setw(8) << center[1]
		<< ::std::setw(8) << center[2];
	BOOST_LOG_CHANNEL_SEV(lg, "neb gfx", debug) << ::std::setw(8) << "up"
		<< ::std::setw(8) << up[0]
		<< ::std::setw(8) << up[1]
		<< ::std::setw(8) << up[2];

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






