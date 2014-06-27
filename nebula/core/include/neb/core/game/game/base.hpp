#ifndef NEBULA_GAME_HPP
#define NEBULA_GAME_HPP

#include <neb/core/game/trigger/util/parent.hpp>

namespace neb {
	
	namespace core { namespace scene {
		class base;
	}}
	
	namespace game { namespace game {

	namespace util {
		class parent;
	}

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

