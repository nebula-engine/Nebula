#ifndef PHYSX_GAME_WEAPON_BASE_HPP
#define PHYSX_GAME_WEAPON_BASE_HPP

#include <gal/stl/child.hpp>

#include <neb/core/itf/shared.hpp>
#include <neb/core/input/sink.hpp>
//#include <neb/phx/core/actor/util/decl.hpp>

namespace neb {

	namespace core { namespace input {
		class source;
	}}


	namespace game { namespace weapon {
		namespace util {
			class parent;
		}

		class base:
			virtual public neb::itf::shared,
			virtual public neb::core::input::sink,
			virtual public gal::stl::child<neb::game::weapon::util::parent>
		{
			public:
				typedef neb::game::weapon::util::parent parent_t;
				base();
				virtual void					init(parent_t * const & p);

				virtual void					step(gal::etc::timestep const &) {}
				virtual void					connect(std::shared_ptr<neb::core::input::source> src) = 0;
				virtual int					key_fun(std::shared_ptr<neb::core::input::source> window, int, int, int, int) = 0;
				virtual void					fire() = 0;

				/** @brief last
				 *
				 * last time weapon was fired
				 */
				double						last_;
				/** @brief cooldown
				 */
				double						cooldown_;


		};

	}}

}

#endif


