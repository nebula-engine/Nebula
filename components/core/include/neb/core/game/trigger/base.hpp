#ifndef NEB_GAME_TRIGGER_HPP
#define NEB_GAME_TRIGGER_HPP

#include <neb/core/itf/shared.hpp>
#include <neb/core/util/typedef.hpp>


namespace neb { namespace game { namespace trigger {

	namespace util {
		class parent;
	}

	class base: virtual public neb::itf::shared
	{
		public:
			base(std::shared_ptr<neb::game::trigger::util::parent> parent);
			
			virtual void						doSomething() = 0;
			
		public:
			std::weak_ptr<neb::game::trigger::util::parent>		parent_;
	};



}}}


#endif

