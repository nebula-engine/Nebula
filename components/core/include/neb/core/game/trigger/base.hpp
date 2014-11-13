#ifndef NEB_GAME_TRIGGER_HPP
#define NEB_GAME_TRIGGER_HPP

<<<<<<< HEAD
#include <neb/core/itf/shared.hpp>
=======
#include <gal/stl/child.hpp>

#include <neb/core/itf/shared.hpp>

>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
#include <neb/core/util/typedef.hpp>


namespace neb { namespace game { namespace trigger {

	namespace util {
		class parent;
	}

<<<<<<< HEAD
	class base: virtual public neb::itf::shared
	{
		public:
			base(std::shared_ptr<neb::game::trigger::util::parent> parent);
			
			virtual void						doSomething() = 0;
			
		public:
			std::weak_ptr<neb::game::trigger::util::parent>		parent_;
=======
	class base:
		virtual public neb::itf::shared,
		virtual public gal::stl::child<neb::game::trigger::util::parent>
	{
		public:
			typedef neb::game::trigger::util::parent	parent_t;

			base();
			virtual void					step(gal::etc::timestep const &);
			virtual void					doSomething() = 0;
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
	};



}}}


#endif

