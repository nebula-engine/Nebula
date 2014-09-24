#ifndef NEBULA_GAME_HPP
#define NEBULA_GAME_HPP

#include <neb/core/core/scene/util/decl.hpp>
#include <neb/core/game/game/util/decl.hpp>
#include <neb/core/game/trigger/util/parent.hpp>

using namespace std;

namespace neb {
	namespace game {
		namespace game {
			class base:
				virtual public neb::game::trigger::util::parent
			{
				public:
					/** @brief %Scene.
					 * Currently a game is fully defined by a single scene.
					 * The game will load a scene from an Xml file.
					 */
					weak_ptr<neb::core::core::scene::base>			scene_;

					weak_ptr<neb::game::game::util::parent>			parent_;

					//gal::map<std::shared_ptr<neb::Game::Player> >   players_;

			};
		}
	}
}


#endif

