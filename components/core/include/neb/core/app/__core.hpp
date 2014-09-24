#ifndef __NEBULA_APP___CORE_H__
#define __NEBULA_APP___CORE_H__

#include <neb/core/app/__base.hpp>
#include <neb/core/core/scene/util/parent.hpp>
<<<<<<< HEAD

using namespace std;
=======
#include <neb/core/game/game/util/parent.hpp>
#include <neb/core/game/game/util/decl.hpp>
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507

namespace neb {
	namespace app {
		class __core:
			virtual public neb::core::app::__base,
<<<<<<< HEAD
			virtual public neb::core::core::scene::util::parent
		{
			protected:
				virtual void			__init();
			public:
				virtual void			release() {}
				static weak_ptr<neb::app::__core>	global();
				neb::core::pose			getPose();
				neb::core::pose			getPoseGlobal();
=======
			virtual public neb::core::core::scene::util::parent,
			virtual public neb::game::game::util::parent
		{
			protected:
				virtual void				__init();
				virtual void				__release();
				void					__step(gal::etc::timestep const &);
			public:
				static weak_ptr<neb::app::__core>	global();
				neb::core::pose				getPose() const;
				neb::core::pose				getPoseGlobal() const;


				std::shared_ptr<neb::game::game::base>			createGame(
						neb::game::game::desc const &
						);
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
		};
	}
}

#endif





