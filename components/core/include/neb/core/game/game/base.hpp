#ifndef NEBULA_GAME_HPP
#define NEBULA_GAME_HPP

#include <neb/core/core/scene/util/decl.hpp>
#include <neb/core/game/game/util/decl.hpp>
#include <neb/core/game/trigger/util/parent.hpp>
#include <neb/core/game/ai/util/parent.hpp>


namespace neb {
	namespace game {
		namespace game {
			namespace util {
				class parent;
			}

			class base:
				virtual public gal::stl::child<neb::game::game::util::parent>,
				virtual public neb::game::trigger::util::parent,
				virtual public neb::game::ai::util::parent
			{
				public:
					typedef neb::game::game::util::parent parent_t;
					
					virtual void		init(parent_t * const &);
					virtual void		release();
					virtual void		step(gal::etc::timestep const & ts);

					/** @brief %Scene.
					 * Currently a game is fully defined by a single scene.
					 * The game will load a scene from an Xml file.
					 */
					std::weak_ptr<neb::core::core::scene::base>			scene_;

					//gal::map<std::shared_ptr<neb::Game::Player> >   players_;

			};
		}
	}
}


#endif

