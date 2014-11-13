#ifndef PHYSX_CORE_ACTOR_BASE
#define PHYSX_CORE_ACTOR_BASE

#include <neb/core/core/actor/base.hpp>

#include <neb/phx/core/actor/util/cast.hpp>
#include <neb/phx/core/actor/util/decl.hpp>
#include <neb/phx/core/actor/util/parent.hpp>
#include <neb/phx/core/shape/util/parent.hpp>
<<<<<<< HEAD
#include <neb/phx/game/weapon/util/parent.hpp>
#include <neb/phx/game/weapon/util/decl.hpp>
#include <neb/phx/filter.hpp>
=======
//#include <neb/core/game/weapon/util/parent.hpp>
#include <neb/core/game/weapon/util/decl.hpp>
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507

namespace neb { namespace phx { namespace core { namespace actor {

	class base:
		virtual public neb::core::core::actor::base,
<<<<<<< HEAD
		virtual public neb::phx::core::actor::util::parent,
		virtual public neb::phx::core::shape::util::parent,
		virtual public neb::phx::game::weapon::util::parent,
		virtual public neb::phx::core::actor::util::cast
	{
		public:
			base(std::shared_ptr<neb::phx::core::actor::util::parent> parent);

			
			virtual void		init();
=======
		virtual public neb::phx::core::actor::util::cast
	{
		public:
			base();
			virtual ~base();
			
			virtual void		init(neb::core::core::actor::util::parent * const & p);
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
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
<<<<<<< HEAD
				ar & boost::serialization::make_nvp("filter_data_simulation",simulation_);
				ar & boost::serialization::make_nvp("filter_data_scene_query",scene_query_);

			}
	
			std::shared_ptr<neb::phx::core::actor::util::parent>			getPxParent();
=======
				//ar & boost::serialization::make_nvp("filter_data_simulation",simulation_);
				//ar & boost::serialization::make_nvp("filter_data_scene_query",scene_query_);

			}
	
			//std::shared_ptr<neb::phx::core::actor::util::parent>			getPxParent();
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507

			/** @name convenience functions
			 * @{
			 */
			/** @brief create simple projectile weapon
			 */
<<<<<<< HEAD
			std::weak_ptr<neb::phx::game::weapon::SimpleProjectile>			createWeaponSimpleProjectile(
					std::shared_ptr<neb::gfx::window::base> window,
=======
			std::weak_ptr<neb::game::weapon::SimpleProjectile>			createWeaponSimpleProjectile(
					std::shared_ptr<neb::core::input::source> src,
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
					double size,
					double damage,
					double velocity);
			/** @} */
<<<<<<< HEAD
		public:
			std::weak_ptr<neb::phx::core::actor::util::parent>			parent_;

			phx::filter::data							simulation_;
			phx::filter::data							scene_query_;

			double									health_;
=======
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507

	};


}}}}

#endif
