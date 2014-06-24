#ifndef NEB_GAME_TRIGGER_HPP
#define NEB_GAME_TRIGGER_HPP

#include <Nebula/util/shared.hpp>
#include <Nebula/util/typedef.hpp>
#include <Nebula/game/trigger/util/decl.hpp>


namespace neb { namespace game { namespace trigger {


	class base: virtual public neb::std::shared
	{
		public:
			base(sp::shared_ptr<neb::game::trigger::util::parent> parent);
			
			virtual void						doSomething() = 0;
			
		public:
			sp::weak_ptr<neb::game::trigger::util::parent>		parent_;
	};



}}}


#endif

