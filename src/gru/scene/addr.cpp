
#include <gru/scene/desc.hpp>
#include <gru/scene/scene.hpp>


void		glutpp::scene::addr::load(boost::shared_ptr<glutpp::scene::scene> scene) {
	vec_.push_back(scene->i());
}



