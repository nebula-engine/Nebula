#ifndef NEBULA_GAME_MAP_HPP
#define NEBULA_GAME_MAP_HPP

//#include <neb/core/scene/Local.hh>
#include <neb/game/spawn/util/parent.hpp>

namespace neb { namespace game { namespace map {

	class base:
		virtual public neb::core::scene::local,
		virtual public neb::game::spawn::util::parent
	{
		public:
			base(sp::shared_ptr<neb::core::scene::util::parent> parent);
			
			virtual void		init();
			virtual void		release();
	};



}}}


#endif

