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

#include <PhysX/simulation_callback.hh>

//#include <glutpp/shader.h>

#define LIGHT_MAX 20

namespace px { namespace core { namespace scene {
		/** 
		 * @ingroup group_core
		 * @brief Base
		 */
		class base: virtual public neb::Scene::Base {
			public:
				base(sp::shared_ptr< ::neb::Scene::Util::Parent > parent);
				virtual ~base();
				void					init();
				void					release();
				void					step(::neb::core::TimeStep const & ts);
				/** @} */

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

				px::simulation_callback*		simulation_callback_;

				vec3					gravity_;



};

}}}

#endif





