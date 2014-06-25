#include <neb/debug.hh>
#include <neb/app/Base.hh>
#include <neb/core/scene/Base.hh>

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
	
	auto scene = isPxSceneBase();
	
	if(scene) return scene;
	
	auto actor = isPxActorBase();
	
	if(!actor) throw 0;
	
	return actor->getPxParent()->phx::core::actor::util::parent::getScene();
}



