#ifndef PHYSX_CORE_SCENE_BASE_HPP
#define PHYSX_CORE_SCENE_BASE_HPP

#include <vector>

#include <PxPhysicsAPI.h>

#include <Galaxy-Standard/flag.hpp>
#include <Galaxy-Standard/map.hpp>


#include <Nebula/Types.hh>
#include <Nebula/Util/typedef.hpp>
#include <Nebula/Math/Serialization/GLM.hpp>

#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>

#include <Nebula/Scene/Base.hh>


//#include <Nebula/Actor/Base.hh>
#include <Nebula/Actor/Util/Parent.hh>

#include <Nebula/Graphics/Camera/View/Base.hh>

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
		virtual public neb::Scene::base,
		virtual public phx::core::actor::util::parent
	{
		public:
			base(sp::shared_ptr< ::neb::Scene::util::parent > parent);
			virtual ~base();
			void					init();
			void					release();
			void					step(::neb::core::TimeStep const & ts);



			virtual void				fire(sp::shared_ptr<phx::core::actor::base> actor) = 0;
		public:
			void					create_physics();

			virtual  void				serialize(boost::archive::polymorphic_iarchive & ar, unsigned int const & version) {
				ar & boost::serialization::make_nvp("gravity",gravity_);
			}
			virtual void				serialize(boost::archive::polymorphic_oarchive & ar, unsigned int const & version) {
				ar & boost::serialization::make_nvp("gravity",gravity_);
			}
		public:
			physx::PxScene*				px_scene_;

			physx::PxSimulationFilterShader		px_filter_shader_;

			phx::simulation_callback*		simulation_callback_;

			vec3					gravity_;


			//neb::vehicle_manager					vehicle_manager_;


	};

}}}

#endif





