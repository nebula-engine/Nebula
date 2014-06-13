

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
	up_(0, 1, 0),
	key_n_(GLFW_KEY_H),
	key_s_(GLFW_KEY_N),
	key_e_(GLFW_KEY_L),
	key_w_(GLFW_KEY_J),
	key_u_(GLFW_KEY_I),
	key_d_(GLFW_KEY_K)
{

	float s = 1;
	float d = 0.707;

	s *= 1.5;
	d *= 1.5;



	head_[0] = vec3(  0, 0, -s );
	head_[1] = vec3(  d, 0, -d );
	head_[2] = vec3(  s, 0,  0 );
	head_[3] = vec3(  d, 0,  d );
	head_[4] = vec3(  0, 0,  s );
	head_[5] = vec3( -d, 0,  d );
	head_[6] = vec3( -s, 0,  0 );
	head_[7] = vec3( -d, 0, -d );

	head_flag_[neb::gfx::camera::view::util::flag::NORTH								] = 0;
	head_flag_[neb::gfx::camera::view::util::flag::NORTH	|	neb::gfx::camera::view::util::flag::EAST	] = 1;
	head_flag_[							neb::gfx::camera::view::util::flag::EAST	] = 2;
	head_flag_[neb::gfx::camera::view::util::flag::SOUTH	|	neb::gfx::camera::view::util::flag::EAST	] = 3;
	head_flag_[neb::gfx::camera::view::util::flag::SOUTH								] = 4;
	head_flag_[neb::gfx::camera::view::util::flag::SOUTH	|	neb::gfx::camera::view::util::flag::WEST	] = 5;
	head_flag_[							neb::gfx::camera::view::util::flag::WEST	] = 6;
	head_flag_[neb::gfx::camera::view::util::flag::NORTH	|	neb::gfx::camera::view::util::flag::WEST	] = 7;


}
void	neb::gfx::Camera::View::Free::init() {

}
void			neb::gfx::Camera::View::Free::connect(sp::shared_ptr<neb::gfx::Window::Base> const & window) {
	BOOST_LOG_CHANNEL_SEV(lg, "neb gfx camera view", info) << __PRETTY_FUNCTION__;

	/*conns_.key_fun_ =*/ window->sig_.key_fun_.connect(
			20,
			::std::bind(&neb::gfx::Camera::View::Free::key_fun,
				this,
				::std::placeholders::_1,
				::std::placeholders::_2,
				::std::placeholders::_3,
				::std::placeholders::_4,
				::std::placeholders::_5
				));

	/*	conns_.mouse_button_fun_ = window->sig_.mouse_button_fun_.connect(
		::std::bind(&neb::gfx::gui::Layout::Base::mouse_button_fun,
		this,
		::std::placeholders::_1,
		::std::placeholders::_2,
		::std::placeholders::_3,
		::std::placeholders::_4
		));
	 */

}
int			neb::gfx::Camera::View::Free::key_fun(
		sp::shared_ptr<neb::gfx::Window::Base> const & window,
		int key,
		int scancode,
		int action,
		int mods)
{
	BOOST_LOG_CHANNEL_SEV(lg, "neb gfx camera view", debug) << __PRETTY_FUNCTION__;


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
	}
	return 0;
}
void			neb::gfx::Camera::View::Free::step(neb::core::TimeStep const & ts) {
	BOOST_LOG_CHANNEL_SEV(lg, "neb gfx camera view", debug) << __PRETTY_FUNCTION__;

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
	quat q(yaw_,y);


	vec3 v(move());
	v *= ts.dt;
	v *= 1.0;

	v = q * v;

	eye_ += vec4(v, 0.0f);
}

vec3			neb::gfx::Camera::View::Free::move() {
	BOOST_LOG_CHANNEL_SEV(lg, "neb gfx camera view", debug) << __PRETTY_FUNCTION__;

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

	return mov;
}

mat4		neb::gfx::Camera::View::Free::view() {
	printf("%s\n", __FUNCTION__);

	vec3 up(0,1,0);
	vec3 look(0,0,-1);


	quat rot(yaw_, vec3(0,1,0));

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






