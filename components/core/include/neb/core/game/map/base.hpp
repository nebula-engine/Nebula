#ifndef NEBULA_GAME_MAP_HPP
#define NEBULA_GAME_MAP_HPP

#include <neb/core/core/scene/base.hpp>
#include <neb/core/game/spawn/util/parent.hpp>

namespace neb { namespace game { namespace map {

	class base:
		virtual public neb::core::core::scene::base,
		virtual public neb::game::spawn::util::parent
	{
		public:
			base();
			
			virtual void		init(parent_t * const & p);
			virtual void		release();
	};



}}}


#endif

