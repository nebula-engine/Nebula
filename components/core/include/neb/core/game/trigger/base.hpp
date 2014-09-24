#ifndef NEB_GAME_TRIGGER_HPP
#define NEB_GAME_TRIGGER_HPP

#include <gal/stl/child.hpp>

#include <neb/core/itf/shared.hpp>

#include <neb/core/util/typedef.hpp>


namespace neb { namespace game { namespace trigger {

	namespace util {
		class parent;
	}

	class base:
		virtual public neb::itf::shared,
		virtual public gal::stl::child<neb::game::trigger::util::parent>
	{
		public:
			typedef neb::game::trigger::util::parent	parent_t;

			base();
			virtual void					step(gal::etc::timestep const &);
			virtual void					doSomething() = 0;
	};



}}}


#endif

