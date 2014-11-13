#ifndef NEBULA_GAME_SPAWN_BASE_HPP
#define NEBULA_GAME_SPAWN_BASE_HPP

<<<<<<< HEAD
=======
#include <neb/core/itf/shared.hpp>
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
#include <neb/core/pose.hpp>

namespace neb { namespace game { namespace spawn {

<<<<<<< HEAD
	class base: virtual public neb::itf::shared {
		public:

			neb::core::pose		pose_;

			
	};

	
=======
	namespace util {
		class parent;
	}

	class base: virtual public neb::itf::shared
	{

		public:
			typedef neb::game::spawn::util::parent parent_t;

			neb::core::pose		pose_;

			virtual void		init(parent_t * const & p);			
			virtual void		step(gal::etc::timestep const &);

	};


>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
}}}

#endif
