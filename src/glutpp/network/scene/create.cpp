#include <glutpp/network/message.h>

void glutpp::network::scene::create::load(glutpp::scene::scene_shared scene) {

	glutpp::scene::desc_shared desc(new glutpp::scene::desc);

	std::get<1>(tup_)->load(scene);
	std::get<0>(tup_)->load(scene);
}

