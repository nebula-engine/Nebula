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
<<<<<<< HEAD
			base(std::shared_ptr<neb::core::core::scene::util::parent> parent);
			
			virtual void		init();
=======
			base();
			
			virtual void		init(parent_t * const & p);
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
			virtual void		release();
	};



}}}


#endif

