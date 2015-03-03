#ifndef PHYSX_CORE_ACTOR_BASE
#define PHYSX_CORE_ACTOR_BASE

#include <gal/stl/verbosity.hpp>

#include <neb/fnd/plug/phx/core/actor/Base.hpp>


#include <neb/phx/tmp/Child.hpp>
#include <neb/phx/core/actor/util/cast.hpp>
#include <neb/phx/core/actor/util/decl.hpp>
#include <neb/phx/core/actor/util/parent.hpp>
//#include <neb/phx/core/shape/util/parent.hpp>
//#include <neb/fnd/game/weapon/util/parent.hpp>
#include <neb/fnd/game/weapon/util/decl.hpp>

namespace neb { namespace phx { namespace core { namespace actor {
	class base:
		public gal::tmp::Verbosity<neb::phx::core::actor::base>,
		virtual public neb::fnd::plug::phx::core::actor::Base,
		virtual public neb::phx::core::actor::util::cast
	{
		public:
			base();
			virtual ~base();
			virtual void		init(parent_t * const & p);
			virtual void		release() = 0;
			virtual void		step(gal::etc::timestep const & ts);
			/** 
			 * empty function implemented so that base object can be allocated (for making lights for instance)
			 * @todo in future, light actors done need to BE phx actors
			 */
			virtual void		create_physics();
			virtual void		init_physics();
			virtual void		set_pose_global(gal::math::pose const & pose);

			template<typename Archive> void		serializeTemplate(Archive & ar, unsigned int const & version) {
				//ar & boost::serialization::make_nvp("filter_data_simulation",simulation_);
				//ar & boost::serialization::make_nvp("filter_data_scene_query",scene_query_);

			}
	
			//std::shared_ptr<neb::phx::core::actor::util::parent>			getPxParent();

			/** @name convenience functions
			 * @{
			 */
			/** @} */

	};


}}}}

#endif
