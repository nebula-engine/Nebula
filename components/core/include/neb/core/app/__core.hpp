#ifndef __NEBULA_APP___CORE_H__
#define __NEBULA_APP___CORE_H__

#include <neb/core/app/__base.hpp>
#include <neb/core/core/scene/util/parent.hpp>
#include <neb/core/game/game/util/parent.hpp>
#include <neb/core/game/game/util/decl.hpp>

namespace neb {
	namespace app {
		class __core:
			virtual public neb::core::app::__base,
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
		};
	}
}

#endif





