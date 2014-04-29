
#include <gru/network/message.hpp>
#include <gru/scene/addr.hpp>
#include <gru/scene/raw.hpp>
#include <gru/scene/scene.hpp>

void glutpp::network::scene::create::load(glutpp::scene::scene_s scene) {

	addr_.load(scene);
	desc_.load(scene);
}

