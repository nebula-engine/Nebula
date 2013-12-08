


void	camera_control::init()
{
	vec_z_.push_back(
			window_->map_sig_key_down_['w'].connect(
				std::bind(&glutpp::camera_control::callback_w_, 1.0)));

	vec_z_.push_back(
			window_->map_sig_key_up_['w'].connect(
				std::bind(&glutpp::camera_control::callback_w_, -1.0)));

}
void	camera_control::callback_z_(float s)
{
	z_ += s;
}



