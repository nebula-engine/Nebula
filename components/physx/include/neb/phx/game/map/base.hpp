#ifndef PHYSX_GAME_MAP_HPP
#define PHYSX_GAME_MAP_HPP


#include <neb/core/game/map/base.hpp>

#include <neb/phx/core/scene/base.hpp>

namespace neb { namespace phx {

	namespace core { namespace scene { namespace util {
		class parent;
	}}}


	namespace game { namespace map {

		class base:
			virtual public neb::phx::core::scene::base,
			virtual public neb::game::map::base
		{
			public:
				base(std::shared_ptr<neb::phx::core::scene::util::parent> parent);

				virtual void			init();
				virtual void			release();
		};



	}}
}}


#endif

