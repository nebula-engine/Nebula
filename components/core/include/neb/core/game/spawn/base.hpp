#ifndef NEBULA_GAME_SPAWN_BASE_HPP
#define NEBULA_GAME_SPAWN_BASE_HPP

#include <neb/core/itf/shared.hpp>
#include <neb/core/pose.hpp>

namespace neb { namespace game { namespace spawn {

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


}}}

#endif
