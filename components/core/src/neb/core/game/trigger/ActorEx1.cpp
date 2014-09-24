
#include <neb/core/app/__base.hpp>
#include <neb/core/core/actor/base.hpp>
#include <neb/core/core/scene/base.hpp>
#include <neb/core/core/scene/util/parent.hpp>
#include <neb/core/game/game/base.hpp>
#include <neb/core/game/game/util/parent.hpp>
#include <neb/core/game/trigger/util/parent.hpp>
#include <neb/core/game/trigger/ActorEx1.hpp>

neb::game::trigger::ActorEx1::ActorEx1(std::shared_ptr<neb::game::trigger::util::parent> parent):
	neb::game::trigger::base(parent)
{
}
void				neb::game::trigger::ActorEx1::connect(std::shared_ptr<neb::core::core::actor::base> actor) {
	
	auto self(dynamic_pointer_cast<neb::game::trigger::ActorEx1>(shared_from_this()));
	
	typedef boost::signals2::signal<void()> signal_type;

	actor->sig_release_.connect(
			signal_type::slot_type(
				&neb::game::trigger::ActorEx1::doSomething,
				self
				).track_foreign(self)
			);
}
void				neb::game::trigger::ActorEx1::doSomething() {
	auto parent(parent_.lock());
	assert(parent);
	
	auto game(dynamic_pointer_cast<neb::game::game::base>(parent));
	assert(game);
	
	auto scene(game->scene_.lock());
	
	if(!scene) return;

	auto scene_parent = scene->getParent().lock();
	
	assert(scene_parent);
	
	scene_parent->neb::core::core::scene::util::parent::erase(scene->i_);
	
	// message
	auto app = neb::core::app::__base::global();
	if(app->console_) app->console_->operator<<("you won!");

	//scene->getParent()->erase(scene->i_);
	
//	auto gp(game->parent_.lock());
	
//	gp->erase(parent->i_);
	
}

