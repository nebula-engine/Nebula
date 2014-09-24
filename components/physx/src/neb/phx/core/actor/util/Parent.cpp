
<<<<<<< HEAD
#include <neb/core/util/debug.hpp>
#include <neb/core/core/scene/base.hpp>

#include <neb/phx/core/scene/base.hpp>
#include <neb/phx/core/actor/base.hpp>
#include <neb/phx/core/actor/util/parent.hpp>


neb::phx::core::actor::util::parent::parent() {
}
neb::phx::core::actor::util::parent::~parent() {
}
void							neb::phx::core::actor::util::parent::init() {
	neb::core::core::actor::util::parent::init();
}
std::shared_ptr<neb::phx::core::scene::base>			neb::phx::core::actor::util::parent::getScene() {
	
	auto scene(std::dynamic_pointer_cast<neb::phx::core::scene::base>(shared_from_this()));
	
	if(scene) return scene;

	auto actor(std::dynamic_pointer_cast<neb::phx::core::actor::base>(shared_from_this()));
	
	if(!actor) throw 0;
	
	return actor->getPxParent()->neb::phx::core::actor::util::parent::getScene();
}



=======
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
