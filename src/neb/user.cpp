#include <neb/user.h>
#include <neb/actor/Rigid_Body.h>

neb::user::user()
{}
void	neb::user::connect(std::shared_ptr<glutpp::window> w)
{

	std::shared_ptr<neb::actor::Rigid_Body> actor = std::dynamic_pointer_cast<neb::actor::Rigid_Body>(actor_);

	w->map_sig_key_[GLFW_KEY_E].connect(std::bind(
				&neb::actor::Rigid_Body::key_force,
				actor,
				std::placeholders::_1,
				std::placeholders::_2,
				std::placeholders::_3,
				math::vec3(0.0, 1.0, 0.0)));
	w->map_sig_key_[GLFW_KEY_Q].connect(std::bind(
				&neb::actor::Rigid_Body::key_force,
				actor,
				std::placeholders::_1,
				std::placeholders::_2,
				std::placeholders::_3,
				math::vec3(0.0,-1.0, 0.0)));


	w->map_sig_key_[GLFW_KEY_W].connect(std::bind(
				&neb::actor::Rigid_Body::key_force,
				actor,
				std::placeholders::_1,
				std::placeholders::_2,
				std::placeholders::_3,
				math::vec3(0.0, 0.0,-1.0)));
	w->map_sig_key_[GLFW_KEY_S].connect(std::bind(
				&neb::actor::Rigid_Body::key_force,
				actor,
				std::placeholders::_1,
				std::placeholders::_2,
				std::placeholders::_3,
				math::vec3(0.0, 0.0, 1.0)));


	w->map_sig_key_[GLFW_KEY_D].connect(std::bind(
				&neb::actor::Rigid_Body::key_force,
				actor,
				std::placeholders::_1,
				std::placeholders::_2,
				std::placeholders::_3,
				math::vec3( 1.0, 0.0, 0.0)));
	w->map_sig_key_[GLFW_KEY_A].connect(std::bind(
				&neb::actor::Rigid_Body::key_force,
				actor,
				std::placeholders::_1,
				std::placeholders::_2,
				std::placeholders::_3,
				math::vec3(-1.0, 0.0, 0.0)));



	w->map_sig_key_[GLFW_KEY_I].connect(std::bind(
				&neb::actor::Rigid_Body::key_torque,
				actor,
				std::placeholders::_1,
				std::placeholders::_2,
				std::placeholders::_3,
				math::vec3(-1.0, 0.0, 0.0)));
	w->map_sig_key_[GLFW_KEY_K].connect(std::bind(
				&neb::actor::Rigid_Body::key_torque,
				actor,
				std::placeholders::_1,
				std::placeholders::_2,
				std::placeholders::_3,
				math::vec3( 1.0, 0.0, 0.0)));

	w->map_sig_key_[GLFW_KEY_L].connect(std::bind(
				&neb::actor::Rigid_Body::key_torque,
				actor,
				std::placeholders::_1,
				std::placeholders::_2,
				std::placeholders::_3,
				math::vec3( 0.0,-1.0, 0.0)));
	w->map_sig_key_[GLFW_KEY_J].connect(std::bind(
				&neb::actor::Rigid_Body::key_torque,
				actor,
				std::placeholders::_1,
				std::placeholders::_2,
				std::placeholders::_3,
				math::vec3( 0.0, 1.0, 0.0)));
	w->map_sig_key_[GLFW_KEY_O].connect(std::bind(
				&neb::actor::Rigid_Body::key_torque,
				actor,
				std::placeholders::_1,
				std::placeholders::_2,
				std::placeholders::_3,
				math::vec3( 0.0, 0.0,-1.0)));
	w->map_sig_key_[GLFW_KEY_U].connect(std::bind(
				&neb::actor::Rigid_Body::key_torque,
				actor,
				std::placeholders::_1,
				std::placeholders::_2,
				std::placeholders::_3,
				math::vec3( 0.0, 0.0, 1.0)));



	w->map_sig_key_[GLFW_KEY_SPACE].connect(std::bind(
				&neb::actor::Base::fire,
				actor,
				std::placeholders::_1,
				std::placeholders::_2,
				std::placeholders::_3));

}

