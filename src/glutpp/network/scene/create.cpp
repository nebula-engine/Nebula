#include <glutpp/network/message.h>

#include <glutpp/scene/addr.h>
#include <glutpp/scene/raw.h>
#include <glutpp/scene/scene.h>

void glutpp::network::scene::create::load(glutpp::scene::scene_s scene) {

	glutpp::scene::desc_s desc(new glutpp::scene::desc);

	std::get<1>(tup_)->load(scene);
	std::get<0>(tup_)->load(scene);
}

