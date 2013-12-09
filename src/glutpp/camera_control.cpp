#include <glutpp/window.h>
#include <glutpp/camera_control.h>


void	glutpp::camera_control::init(glutpp::window* window)
{
	window_ = window;
	
	vec_x_.push_back(
			window_->map_sig_key_down_['d'].connect(
				std::bind(&glutpp::camera_control::callback_x_, this, 0, 1.0)));

	vec_x_.push_back(
			window_->map_sig_key_up_['d'].connect(
				std::bind(&glutpp::camera_control::callback_x_, this, 0, 0.0)));

	vec_x_.push_back(
			window_->map_sig_key_down_['a'].connect(
				std::bind(&glutpp::camera_control::callback_x_, this, 1, -1.0)));

	vec_x_.push_back(
			window_->map_sig_key_up_['a'].connect(
				std::bind(&glutpp::camera_control::callback_x_, this, 1, 0.0)));

	vec_y_.push_back(
			window_->map_sig_key_down_['e'].connect(
				std::bind(&glutpp::camera_control::callback_y_, this, 0, 1.0)));

	vec_y_.push_back(
			window_->map_sig_key_up_['e'].connect(
				std::bind(&glutpp::camera_control::callback_y_, this, 0, 0.0)));

	vec_y_.push_back(
			window_->map_sig_key_down_['c'].connect(
				std::bind(&glutpp::camera_control::callback_y_, this, 1, -1.0)));

	vec_y_.push_back(
			window_->map_sig_key_up_['c'].connect(
				std::bind(&glutpp::camera_control::callback_y_, this, 1, 0.0)));

	vec_z_.push_back(
			window_->map_sig_key_down_['w'].connect(
				std::bind(&glutpp::camera_control::callback_z_, this, 0, -1.0)));

	vec_z_.push_back(
			window_->map_sig_key_up_['w'].connect(
				std::bind(&glutpp::camera_control::callback_z_, this, 0, 0.0)));

	vec_z_.push_back(
			window_->map_sig_key_down_['s'].connect(
				std::bind(&glutpp::camera_control::callback_z_, this, 1, 1.0)));

	vec_z_.push_back(
			window_->map_sig_key_up_['s'].connect(
				std::bind(&glutpp::camera_control::callback_z_, this, 1, 0.0)));


}
int	glutpp::camera_control::callback_x_(int a, float s)
{
	if(a==0) v0_.x = s;
	if(a==1) v1_.x = s;
	
	return 1;
}
int	glutpp::camera_control::callback_y_(int a, float s)
{
	if(a==0) v0_.y = s;
	if(a==1) v1_.y = s;
	
	return 1;
}
int	glutpp::camera_control::callback_z_(int a, float s)
{
	if(a==0) v0_.z = s;
	if(a==1) v1_.z = s;
	
	return 1;
}



