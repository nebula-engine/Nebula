
#include <neb/app/Base.hh>
#include <neb/core/actor/Base.hh>
#include <neb/core/scene/Base.hh>
#include <neb/game/game/base.hpp>
#include <neb/game/game/util/parent.hpp>
#include <neb/game/trigger/util/parent.hpp>
#include <neb/game/trigger/ActorEx1.hpp>

neb::game::trigger::ActorEx1::ActorEx1(sp::shared_ptr<neb::game::trigger::util::parent> parent):
	neb::game::trigger::base(parent)
{
}
void				neb::game::trigger::ActorEx1::connect(sp::shared_ptr<neb::core::actor::base> actor) {
	
	auto self(sp::dynamic_pointer_cast<neb::game::trigger::ActorEx1>(shared_from_this()));
	
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
	
	auto game(sp::dynamic_pointer_cast<neb::game::game::base>(parent));
	assert(game);
	
	auto scene(game->scene_.lock());
	
	if(!scene) return;
	
	auto app(neb::app::base::global());
	
	app->neb::core::scene::util::parent::erase(scene->i_);
	
	//scene->getParent()->erase(scene->i_);
	
//	auto gp(game->parent_.lock());
	
//	gp->erase(parent->i_);
	
}

