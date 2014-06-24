#ifndef NEB_GAME_TRIGGER_ACTOREX1_HPP
#define NEB_GAME_TRIGGER_ACTOREX1_HPP

#include <Nebula/core/actor/Util/Types.hh>
#include <Nebula/game/trigger/util/decl.hpp>
#include <Nebula/game/trigger/base.hpp>

namespace neb { namespace game { namespace trigger {


	class ActorEx1: virtual public neb::game::trigger::base {
		public:
			ActorEx1(sp::shared_ptr<neb::game::trigger::util::parent> parent);
			
			virtual void						connect(sp::shared_ptr<neb::core::actor::base> actor);
			virtual void						doSomething();
			
	};



}}}


#endif

