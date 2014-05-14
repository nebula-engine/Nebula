#include <Nebula/debug.hh>

#include <Nebula/App/Base.hh>

#include <Nebula/Actor/Base.hh>
#include <Nebula/Actor/Util/Parent.hh>
#include <Nebula/Scene/Base.hh>

Neb::Actor::Util::Parent::Parent():
	actors_(Neb::App::Base::global()->factories_.actor_base_)
{
}
Neb::Actor::Base_s		Neb::Actor::Util::Parent::getActor(int i) {
	NEBULA_ACTOR_BASE_FUNC;
	
	auto it = actors_.find(i);
	
	if(it == actors_.end()) return Neb::Actor::Base_s();
	
	return it->second.ptr_;
}
Neb::Actor::Base_s		Neb::Actor::Util::Parent::getActor(Neb::Actor::Util::Address addr) {
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
void					Neb::Actor::Util::Parent::releaseActor(Neb::Actor::Util::index_type i) {
	auto it = actors_.find(i);
	
	if(it == actors_.map_.cend()) throw 0;
	
	// release the actor
	it->second.ptr_->release();
	
	actors_.erase(it);
}
Neb::Scene::Base_s			Neb::Actor::Util::Parent::getScene() {
	NEBULA_ACTOR_BASE_FUNC;

	auto scene = isSceneBase();
	
	if(scene) return scene;
	
	auto actor = isActorBase();
	
	if(!actor) throw 0;
	
	return actor->getScene();
}

