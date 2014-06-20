#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Galaxy-Log/log.hpp>

#include <Nebula/config.hh>
#include <Nebula/gfx/window/Base.hh>
#include <Nebula/gfx/Camera/View/Free.hh>

neb::gfx::Camera::View::Free::Free(sp::shared_ptr<neb::gfx::environ::base> parent):
	neb::gfx::Camera::View::base(parent),
	pitch_(0),
	yaw_(0),
	eye_(0, 0, 0, 0),
	center_(0, 0, -1),
	up_(0, 1, 0),
	key_n_(GLFW_KEY_N),
	key_s_(GLFW_KEY_H),
	key_e_(GLFW_KEY_L),
	key_w_(GLFW_KEY_J),
	key_u_(GLFW_KEY_I),
	key_d_(GLFW_KEY_K),
	key_yaw_pos_(GLFW_KEY_A),
	key_yaw_neg_(GLFW_KEY_D),
	key_pitch_pos_(GLFW_KEY_W),
	key_pitch_neg_(GLFW_KEY_S)
{

	float s = 1;
	float d = 0.707;

	s *= 1.5;
	d *= 1.5;
	
	
	typedef neb::gfx::camera::view::util::flag view_flag;

	head_[0]  = vec3(  0, d, -s );
	head_[1]  = vec3(  d, d, -d );
	head_[2]  = vec3(  s, d,  0 );
	head_[3]  = vec3(  d, d,  d );
	head_[4]  = vec3(  0, d,  s );
	head_[5]  = vec3( -d, d,  d );
	head_[6]  = vec3( -s, d,  0 );
	head_[7]  = vec3( -d, d, -d );

	head_[8]  = vec3(  0, 0, -s );
	head_[9]  = vec3(  d, 0, -d );
	head_[10] = vec3(  s, 0,  0 );
	head_[11] = vec3(  d, 0,  d );
	head_[12] = vec3(  0, 0,  s );
	head_[13] = vec3( -d, 0,  d );
	head_[14] = vec3( -s, 0,  0 );
	head_[15] = vec3( -d, 0, -d );

	head_[16]  = vec3(  0, -d, -s );
	head_[17]  = vec3(  d, -d, -d );
	head_[18]  = vec3(  s, -d,  0 );
	head_[19]  = vec3(  d, -d,  d );
	head_[20]  = vec3(  0, -d,  s );
	head_[21]  = vec3( -d, -d,  d );
	head_[22]  = vec3( -s, -d,  0 );
	head_[23]  = vec3( -d, -d, -d );

	head_[24]  = vec3(  0,-s,  0);
	head_[25]  = vec3(  0, s,  0);

	
	head_flag_[view_flag::NORTH				| view_flag::DOWN	] = 0;
	head_flag_[view_flag::NORTH	|	view_flag::EAST	| view_flag::DOWN	] = 1;
	head_flag_[				view_flag::EAST	| view_flag::DOWN	] = 2;
	head_flag_[view_flag::SOUTH	|	view_flag::EAST	| view_flag::DOWN	] = 3;
	head_flag_[view_flag::SOUTH				| view_flag::DOWN	] = 4;
	head_flag_[view_flag::SOUTH	|	view_flag::WEST	| view_flag::DOWN	] = 5;
	head_flag_[				view_flag::WEST	| view_flag::DOWN	] = 6;
	head_flag_[view_flag::NORTH	|	view_flag::WEST	| view_flag::DOWN	] = 7;

	head_flag_[view_flag::NORTH				] = 8;
	head_flag_[view_flag::NORTH	|	view_flag::EAST	] = 9;
	head_flag_[				view_flag::EAST	] = 10;
	head_flag_[view_flag::SOUTH	|	view_flag::EAST	] = 11;
	head_flag_[view_flag::SOUTH				] = 12;
	head_flag_[view_flag::SOUTH	|	view_flag::WEST	] = 13;
	head_flag_[				view_flag::WEST	] = 14;
	head_flag_[view_flag::NORTH	|	view_flag::WEST	] = 15;

	head_flag_[view_flag::NORTH				| view_flag::UP		] = 16;
	head_flag_[view_flag::NORTH	|	view_flag::EAST	| view_flag::UP		] = 17;
	head_flag_[				view_flag::EAST	| view_flag::UP		] = 18;
	head_flag_[view_flag::SOUTH	|	view_flag::EAST	| view_flag::UP		] = 19;
	head_flag_[view_flag::SOUTH				| view_flag::UP		] = 20;
	head_flag_[view_flag::SOUTH	|	view_flag::WEST	| view_flag::UP		] = 21;
	head_flag_[				view_flag::WEST	| view_flag::UP		] = 22;
	head_flag_[view_flag::NORTH	|	view_flag::WEST	| view_flag::UP		] = 23;

	head_flag_[view_flag::UP		] = 24;
	head_flag_[view_flag::DOWN		] = 25;

}
void	neb::gfx::Camera::View::Free::init() {

}
void			neb::gfx::Camera::View::Free::connect(sp::shared_ptr<neb::gfx::window::base> const & window) {
	BOOST_LOG_CHANNEL_SEV(lg, "neb gfx camera view", info) << __PRETTY_FUNCTION__;
	
	
	
	/*conns_.key_fun_ =*/ window->sig_.key_fun_.connect(
			20,
			neb::Signals::KeyFun::slot_type(
				&neb::gfx::Camera::View::Free::key_fun,
				this,
				_1,
				_2,
				_3,
				_4,
				_5
				).track_foreign(shared_from_this())
			);

	/*	conns_.mouse_button_fun_ = window->sig_.mouse_button_fun_.connect(
		::std::bind(&neb::gfx::gui::layout::base::mouse_button_fun,
		this,
		::std::placeholders::_1,
		::std::placeholders::_2,
		::std::placeholders::_3,
		::std::placeholders::_4
		));
	 */

}
int			neb::gfx::Camera::View::Free::key_fun(
		sp::shared_ptr<neb::gfx::window::base> const & window,
		int key,
		int scancode,
		int action,
		int mods)
{
	BOOST_LOG_CHANNEL_SEV(lg, "neb gfx camera view", debug) << __PRETTY_FUNCTION__;

	long unsigned int f = flag_.val_ & (
			neb::gfx::camera::view::util::flag::NORTH |
			neb::gfx::camera::view::util::flag::SOUTH |
			neb::gfx::camera::view::util::flag::EAST |
			neb::gfx::camera::view::util::flag::WEST |
			neb::gfx::camera::view::util::flag::UP |
			neb::gfx::camera::view::util::flag::DOWN);


	BOOST_LOG_CHANNEL_SEV(lg, "neb gfx camera view", debug)
		<< "key = " << key
		<< " scancode = " << scancode
		<< " action = " << action
		<< " mods = " << mods
		<< " flag = " << f;

	if(action == GLFW_PRESS) {
		if(key == key_w_) {
			flag_.set(neb::gfx::camera::view::util::flag::WEST);
			return 1;
		}
		if(key == key_e_) {
			flag_.set(neb::gfx::camera::view::util::flag::EAST);
			return 1;
		}
		if(key == key_s_) {
			flag_.set(neb::gfx::camera::view::util::flag::SOUTH);
			return 1;
		}
		if(key == key_n_) {
			flag_.set(neb::gfx::camera::view::util::flag::NORTH);
			return 1;
		}
		if(key == key_d_) {
			flag_.set(neb::gfx::camera::view::util::flag::DOWN);
			return 1;
		}
		if(key == key_u_) {
			flag_.set(neb::gfx::camera::view::util::flag::UP);
			return 1;
		}
		if(key == key_yaw_pos_) {
			flag_.set(neb::gfx::camera::view::util::flag::YAW_POS);
			return 1;
		}
		if(key == key_yaw_neg_) {
			flag_.set(neb::gfx::camera::view::util::flag::YAW_NEG);
			return 1;
		}
		if(key == key_pitch_pos_)	{ flag_.set(neb::gfx::camera::view::util::flag::PITCH_POS); return 1; }
		if(key == key_pitch_neg_)	{ flag_.set(neb::gfx::camera::view::util::flag::PITCH_NEG); return 1; }

	} else if(action == GLFW_RELEASE) {
		if(key == key_w_) {
			flag_.unset(neb::gfx::camera::view::util::flag::WEST);
			return 1;
		}
		if(key == key_e_) {
			flag_.unset(neb::gfx::camera::view::util::flag::EAST);
			return 1;
		}
		if(key == key_s_) {
			flag_.unset(neb::gfx::camera::view::util::flag::SOUTH);
			return 1;
		}
		if(key == key_n_) {
			flag_.unset(neb::gfx::camera::view::util::flag::NORTH);
			return 1;
		}
		if(key == key_d_) {
			flag_.unset(neb::gfx::camera::view::util::flag::DOWN);
			return 1;
		}
		if(key == key_u_) {
			flag_.unset(neb::gfx::camera::view::util::flag::UP);
			return 1;
		}
		if(key == key_yaw_pos_)		{ flag_.unset(neb::gfx::camera::view::util::flag::YAW_POS); return 1; }
		if(key == key_yaw_neg_)		{ flag_.unset(neb::gfx::camera::view::util::flag::YAW_NEG); return 1; }
		if(key == key_pitch_pos_)	{ flag_.unset(neb::gfx::camera::view::util::flag::PITCH_POS); return 1; }
		if(key == key_pitch_neg_)	{ flag_.unset(neb::gfx::camera::view::util::flag::PITCH_NEG); return 1; }
	}





	return 0;
}
void			neb::gfx::Camera::View::Free::step(neb::core::TimeStep const & ts) {
	BOOST_LOG_CHANNEL_SEV(lg, "neb gfx camera view", debug) << __PRETTY_FUNCTION__;

	// look vector
	//vec3 look = center_ - vec3(eye_);

	// project to xz-plane
	//look.y = 0.0;
	//glm::normalize(look);

	//vec3 x(1,0,0);
	vec3 y(0,1,0);
	//vec3 z(0,0,-1);

	//vec3 c = glm::cross(z,look);

	//float yaw = asin(glm::length(c));

	//float d = glm::dot(y, c);
	//float e = glm::dot(z, look);

	//if(e < 0) yaw = M_PI - yaw;
	
	
	//yaw *= (d > 0) ? 1.0 : -1.0;
	
	// determine yaw rate and update yaw
	long unsigned int f = flag_.val_ & (
			neb::gfx::camera::view::util::flag::YAW_POS |
			neb::gfx::camera::view::util::flag::YAW_NEG);

	real rate = 1.0;

	if(f == neb::gfx::camera::view::util::flag::YAW_POS) {
		yaw_ -= ts.dt * rate;
	}
	if(f == neb::gfx::camera::view::util::flag::YAW_NEG) {
		yaw_ += ts.dt * rate;
	}
	
	// determine pitch rate and update pitch
	f = flag_.val_ & (
			neb::gfx::camera::view::util::flag::PITCH_POS |
			neb::gfx::camera::view::util::flag::PITCH_NEG);
	
	
	if(f == neb::gfx::camera::view::util::flag::PITCH_POS) {
		pitch_ -= ts.dt * rate;
	}
	if(f == neb::gfx::camera::view::util::flag::PITCH_NEG) {
		pitch_ += ts.dt * rate;
	}
	
	printf("yaw_ = %f\n",yaw_);

	// rotate velocity by camera yaw
	quat q = glm::angleAxis(yaw_,y);
	
	
	
	vec3 v(move());
	v *= ts.dt;
	v *= 1.0;

	printf("v = %f %f %f\n",v.x,v.y,v.z);

	v = q * v;

	printf("v = %f %f %f\n",v.x,v.y,v.z);

	eye_ += vec4(v, 0.0f);
}

vec3			neb::gfx::Camera::View::Free::move() {
	BOOST_LOG_CHANNEL_SEV(lg, "neb gfx camera view", debug) << __PRETTY_FUNCTION__;
	BOOST_LOG_CHANNEL_SEV(lg, "neb gfx camera view", debug) << "flag = " << flag_.val_;

	//	vec3 mov = vec3(0,0,-1) * north_ + vec3(1,0,0) * east_;

	//	return mov;

	vec3 mov(0);

	// ignore all other flags
	long unsigned int f = flag_.val_ & (
			neb::gfx::camera::view::util::flag::NORTH |
			neb::gfx::camera::view::util::flag::SOUTH |
			neb::gfx::camera::view::util::flag::EAST |
			neb::gfx::camera::view::util::flag::WEST |
			neb::gfx::camera::view::util::flag::UP |
			neb::gfx::camera::view::util::flag::DOWN);

	// find vector for move flag
	auto it = head_flag_.find( f );

	if ( it != head_flag_.end() )
	{
		mov = head_[it->second];
	}

	BOOST_LOG_CHANNEL_SEV(lg, "neb gfx camera view", debug) << "flag = " << flag_.val_;

	return mov;
}

mat4		neb::gfx::Camera::View::Free::view() {
	printf("%s\n", __FUNCTION__);

	vec3 x(1,0,0);
	vec3 up(0,1,0);
	vec3 look(0,0,-1);
	
	
	
	quat rot = glm::angleAxis(yaw_, up);
	
	vec3 xp = rot * x;
	
	//rot = rot * glm::angleAxis(pitch_ , xp);
	rot = glm::angleAxis(pitch_ , xp) * rot;

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






