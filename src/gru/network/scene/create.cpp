
#include <gru/network/scene/message.hpp>
#include <gru/scene/addr.hpp>
#include <gru/scene/raw.hpp>
#include <gru/scene/desc.hpp>
#include <gru/scene/scene.hpp>

void glutpp::network::scene::create::load(boost::shared_ptr<glutpp::scene::scene> scene) {

	addr_.load(scene);
	desc_.load(scene);
}

