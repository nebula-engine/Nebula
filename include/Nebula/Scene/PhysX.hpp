#ifndef __GLUTPP_SCENE_H__
#define __GLUTPP_SCENE_H__

#include <vector>

#include <Galaxy-Standard/flag.hpp>
#include <Galaxy-Standard/map.hpp>


#include <Nebula/Types.hh>
#include <Nebula/Util/typedef.hpp>



#include <Nebula/Scene/Util/Flag.hh>
#include <Nebula/Scene/Util/Types.hh>

#include <Nebula/config.hh> // Nebula/config.hpp.in
#include <Nebula/Graphics/glsl/program.hh>


//#include <Nebula/Actor/Base.hh>
#include <Nebula/Actor/Util/Parent.hh>

#include <Nebula/Graphics/Camera/View/Base.hh>

//#include <glutpp/shader.h>

#define LIGHT_MAX 20

namespace neb {
	namespace scene {
		/** 
		 * @ingroup group_core
		 * @brief Base
		 */
		class base: virtual public neb::core::actor::util::parent {
			public:
				Base(sp::shared_ptr<neb::core::scene::util::parent>;
				virtual ~Base();
				void				init();
				void				release();
				glm::mat4			get_pose();
				/** @name Main Loop @{ */
				/** @brief render */
				void				render(
						double time,
						std::shared_ptr<neb::gfx::Camera::View::base>,
						std::shared_ptr<neb::gfx::Camera::Projection::base>,
						sp::shared_ptr<neb::gfx::window::base>;
				void							step(neb::core::TimeStep const & ts);
				/** @} */

				virtual  void						serialize(boost::archive::polymorphic_iarchve & ar, unsigned int const & version) {
					ar & boost::serialization::make_nvp("gravity",gravity_);
				}
				virtual void						serialize(boost::archive::polymorphic_oarchve & ar, unsigned int const & version) {
					ar & boost::serialization::make_nvp("gravity",gravity_);
				}
			public:
				void							create_physics();
			public:
				physx::PxSimulationFilterShader				px_filter_shader_;

				neb::simulation_callback*				simulation_callback_;

				physx::PxScene*						px_scene_;

				//neb::vehicle_manager					vehicle_manager_;

			public:
				glm::vec3						gravity_;
		};
	}
}

#endif





