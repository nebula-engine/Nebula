#ifndef PHYSX_CORE_ACTOR_BASE
#define PHYSX_CORE_ACTOR_BASE

#include <Nebula/core/actor/Base.hh>

#include <PhysX/core/actor/util/cast.hpp>
#include <PhysX/core/actor/util/decl.hpp>
#include <PhysX/core/actor/util/parent.hpp>
#include <PhysX/core/shape/util/parent.hpp>
#include <PhysX/game/weapon/util/parent.hpp>
#include <PhysX/game/weapon/util/decl.hpp>
#include <PhysX/filter.hpp>

namespace phx { namespace core { namespace actor {

	class base:
		virtual public neb::core::actor::base,
		virtual public phx::core::actor::util::parent,
		virtual public phx::core::shape::util::parent,
		virtual public phx::game::weapon::util::parent,
		virtual public phx::core::actor::util::cast
	{
		public:
			base(sp::shared_ptr<phx::core::actor::util::parent> parent);

			
			virtual void		init();
			virtual void		release() = 0;
			virtual void		step(gal::std::timestep const & ts);


			


			void			hit();
			void			damage(real);

			
			virtual void		create_physics() = 0;
			virtual void		init_physics() = 0;

			template<typename Archive> void		serializeTemplate(Archive & ar, unsigned int const & version) {
				ar & boost::serialization::make_nvp("filter_data_simulation",simulation_);
				ar & boost::serialization::make_nvp("filter_data_scene_query",scene_query_);

			}
	
			sp::shared_ptr<phx::core::actor::util::parent>				getPxParent();

			/** @name convenience functions
			 * @{
			 */
			/** @brief create simple projectile weapon
			 */
			sp::weak_ptr<phx::game::weapon::SimpleProjectile>			createWeaponSimpleProjectile(
					sp::shared_ptr<neb::gfx::window::base> window,
					real size,
					real damage,
					real velocity);
			/** @} */
		public:
			sp::weak_ptr<phx::core::actor::util::parent>				parent_;

			phx::filter::data				simulation_;
			phx::filter::data				scene_query_;

			real									health_;

	};


}}}

#endif
