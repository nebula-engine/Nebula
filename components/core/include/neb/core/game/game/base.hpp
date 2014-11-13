#ifndef NEBULA_GAME_HPP
#define NEBULA_GAME_HPP

#include <neb/core/core/scene/util/decl.hpp>
#include <neb/core/game/game/util/decl.hpp>
#include <neb/core/game/trigger/util/parent.hpp>
<<<<<<< HEAD

using namespace std;
=======
#include <neb/core/game/ai/util/parent.hpp>

>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507

namespace neb {
	namespace game {
		namespace game {
<<<<<<< HEAD
			class base:
				virtual public neb::game::trigger::util::parent
			{
				public:
=======
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

>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
					/** @brief %Scene.
					 * Currently a game is fully defined by a single scene.
					 * The game will load a scene from an Xml file.
					 */
<<<<<<< HEAD
					weak_ptr<neb::core::core::scene::base>			scene_;

					weak_ptr<neb::game::game::util::parent>			parent_;
=======
					std::weak_ptr<neb::core::core::scene::base>			scene_;
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507

					//gal::map<std::shared_ptr<neb::Game::Player> >   players_;

			};
		}
	}
}


#endif

