
#include <gru/network/message.hpp>
#include <gru/scene/addr.hpp>
#include <gru/scene/raw.hpp>
#include <gru/scene/scene.hpp>

void glutpp::network::scene::create::load(glutpp::scene::scene_s scene) {

	glutpp::scene::desc_s desc(new glutpp::scene::desc);

	std::get<1>(tup_)->load(scene);
	std::get<0>(tup_)->load(scene);
}

