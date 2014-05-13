#include <Nebula/debug.hpp>
#include <Nebula/Actor/Base.hpp>
#include <Nebula/Actor/Util/Parent.hh>
#include <Nebula/Scene/scene.hpp>

Neb::Actor::Parent::Parent():
	actors_(Neb::App::global()->factories_.actor_base_)
{
}
Neb::Actor::Base_s		Neb::Actor::Util::Parent::getActorBase(int i) {
	NEBULA_ACTOR_BASE_FUNC;
	
	auto it = actors_.find(i);
	
	if(it == actors_.end()) return Neb::Actor::Base_s();
	
	return it->second;
}
Neb::Actor::Base_w		Neb::Actor::Util::Parent::getActorBase(Neb::Actor::Address addr) {
	NEBULA_ACTOR_BASE_FUNC;
	//auto vec = addr->get_vec();
	//assert(vec);
	assert(!addr.vec_.empty());

	int i = addr.vec_.front();
	addr.vec_.pop_front();

	auto actor = getActor(i);
	assert(actor);
	
	if(!addr.vec_.empty()) {
		return actor->getActor(addr);
	}

	return actor;
}
void					Neb::Actor::Parent::releaseActor(Neb::Actor::Util::index_type i) {
	auto it = actors_.find(i);
	
	if(it == actors_.cend()) throw 0;
	
	// release the actor
	it->second.ptr_->release();
	
	actors_.erase(it);
}
Neb::Scene::Base_s			Neb::Actor::parent::getScene() {
	NEBULA_ACTOR_BASE_FUNC;

	auto scene = isSceneBase();
	
	if(scene) return scene;
	
	auto actor = isActorBase();
	
	if(!actor) throw 0;
	
	return actor->getScene();
}

