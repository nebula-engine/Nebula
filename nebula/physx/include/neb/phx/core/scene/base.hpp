#ifndef PHYSX_CORE_SCENE_BASE_HPP
#define PHYSX_CORE_SCENE_BASE_HPP

#include <vector>

#include <PxPhysicsAPI.h>

#include <Galaxy-Standard/flag.hpp>
#include <Galaxy-Standard/map.hpp>


#include <neb/util/decl.hpp>
#include <neb/util/typedef.hpp>
#include <neb/math/Serialization/GLM.hpp>

#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>

#include <neb/core/scene/base.hpp>


//#include <neb/core/actor/base.hpp>
#include <neb/core/actor/util/Parent.hh>

//#include <neb/gfx/Camera/View/Base.hh>

#include <PhysX/core/actor/util/decl.hpp>
#include <PhysX/core/actor/util/parent.hpp>
#include <PhysX/simulation_callback.hh>

//#include <glutpp/shader.h>

#define LIGHT_MAX 20

namespace phx { namespace core { namespace scene {
	/** 
	 * @ingroup group_core
	 * @brief base
	 */
	class base:
		virtual public neb::core::scene::base,
		virtual public phx::core::actor::util::parent
	{
		public:
			base(sp::shared_ptr< ::neb::core::scene::util::parent > parent);
			virtual ~base();
			void					init();
			void					release();
			void					step(::gal::std::timestep const & ts);


		public:
			void					create_physics();

			virtual  void				serialize(boost::archive::polymorphic_iarchive & ar, unsigned int const & version) {
				ar & boost::serialization::make_nvp("gravity",gravity_);
			}
			virtual void				serialize(boost::archive::polymorphic_oarchive & ar, unsigned int const & version) {
				ar & boost::serialization::make_nvp("gravity",gravity_);
			}

			/** @name convenience functions
			 * @{
			 */
			/** @brief create rigidstatic
			 *
			 * @note typeof returned actor will be determined by final implementation of this
			 *
			 * @warning return actor is not initialized
			 */
			sp::weak_ptr<neb::core::actor::base>		createActorRigidStaticUninitialized() = 0;
			/** @} */
		public:
			physx::PxScene*					px_scene_;
			physx::PxSimulationFilterShader			px_filter_shader_;
			phx::simulation_callback*			simulation_callback_;

			vec3					gravity_;


			//neb::vehicle_manager					vehicle_manager_;


	};

}}}

#endif





