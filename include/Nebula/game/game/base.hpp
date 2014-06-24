#ifndef NEBULA_GAME_HPP
#define NEBULA_GAME_HPP

#include <Nebula/core/scene/Util/Types.hh>
#include <Nebula/game/game/util/decl.hpp>
#include <Nebula/game/trigger/util/parent.hpp>

namespace neb { namespace game { namespace game {


	class base:
		virtual public neb::game::trigger::util::parent
	{
		public:
			/** @brief %Scene.
			 * Currently a game is fully defined by a single scene.
			 * The game will load a scene from an Xml file.
			 */
			sp::weak_ptr<neb::core::scene::base>			scene_;

			sp::weak_ptr<neb::game::game::util::parent>		parent_;

			//gal::map<std::shared_ptr<neb::Game::Player> >   players_;

	};

}}}


#endif

