#ifndef PHYSX_CORE_ACTOR_BASE
#define PHYSX_CORE_ACTOR_BASE

#include <neb/core/core/actor/base.hpp>

#include <neb/phx/core/actor/util/cast.hpp>
#include <neb/phx/core/actor/util/decl.hpp>
#include <neb/phx/core/actor/util/parent.hpp>
#include <neb/phx/core/shape/util/parent.hpp>
//#include <neb/core/game/weapon/util/parent.hpp>
#include <neb/core/game/weapon/util/decl.hpp>

namespace neb { namespace phx { namespace core { namespace actor {

	class base:
		virtual public neb::core::core::actor::base,
		virtual public neb::phx::core::actor::util::cast
	{
		public:
			base();
			virtual ~base();
			
			virtual void		init(neb::core::core::actor::util::parent * const & p);
			virtual void		release() = 0;
			virtual void		step(gal::etc::timestep const & ts);

			void			hit();
			void			damage(double);

			
			/** 
			 * empty function implemented so that base object can be allocated (for making lights for instance)
			 * @todo in future, light actors done need to BE phx actors
			 */
			virtual void		create_physics() {}
			virtual void		init_physics() {}

			template<typename Archive> void		serializeTemplate(Archive & ar, unsigned int const & version) {
				//ar & boost::serialization::make_nvp("filter_data_simulation",simulation_);
				//ar & boost::serialization::make_nvp("filter_data_scene_query",scene_query_);

			}
	
			//std::shared_ptr<neb::phx::core::actor::util::parent>			getPxParent();

			/** @name convenience functions
			 * @{
			 */
			/** @brief create simple projectile weapon
			 */
			std::weak_ptr<neb::game::weapon::SimpleProjectile>			createWeaponSimpleProjectile(
					std::shared_ptr<neb::core::input::source> src,
					double size,
					double damage,
					double velocity);
			/** @} */

	};


}}}}

#endif
