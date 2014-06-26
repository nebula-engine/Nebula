#include <neb/debug.hh>
//#include <neb/app/Base.hh>
#include <neb/core/scene/base.hpp>

#include <PhysX/core/scene/base.hpp>
#include <PhysX/core/actor/base.hpp>
#include <PhysX/core/actor/util/parent.hpp>


phx::core::actor::util::parent::parent() {
}
phx::core::actor::util::parent::~parent() {
}
void							phx::core::actor::util::parent::init() {
	neb::core::actor::util::parent::init();
}
sp::shared_ptr<phx::core::scene::base>			phx::core::actor::util::parent::getScene() {
	
	auto scene(sp::dynamic_pointer_cast<phx::core::scene::base>(shared_from_this()));
	
	if(scene) return scene;

	auto actor(sp::dynamic_pointer_cast<phx::core::actor::base>(shared_from_this()));
	
	if(!actor) throw 0;
	
	return actor->getPxParent()->phx::core::actor::util::parent::getScene();
}



