#ifndef __GLUTPP_SCENE_H__
#define __GLUTPP_SCENE_H__

#include <vector>

#include <Nebula/Flag.hh>
#include <Nebula/Util/Map.hh>



#include <Nebula/Types.hh>

#include <Nebula/Scene/Util/Flag.hh>
#include <Nebula/Scene/Util/Types.hh>

#include <Nebula/config.hh> // Nebula/config.hpp.in
#include <Nebula/Graphics/glsl/program.hh>


//#include <Nebula/Actor/Base.hh>
#include <Nebula/Actor/Util/Parent.hh>

#include <Nebula/Graphics/Camera/View/Base.hh>

//#include <glutpp/shader.h>

#define LIGHT_MAX 20

namespace Neb {
	namespace Scene {
		/** 
		 * @ingroup group_core
		 * @brief Base
		 */
		class Base:
			virtual public Neb::Util::Shared,
			virtual public Neb::Actor::Util::Parent
		{
			public:
				Base(Neb::Scene::Util::Parent_s);
				virtual ~Base();
				void				init();
				void				release();
				physx::PxMat44			get_pose();
				/** @name Main Loop @{ */
				/** @brief render */
				void				render(
						double time,
						std::shared_ptr<Neb::Graphics::Camera::View::Base>,
						std::shared_ptr<Neb::Graphics::Camera::Projection::Base>,
						Neb::Graphics::Window::Base_s);
				void				draw(Neb::Graphics::Window::Base_s window);
				void				resize(int w, int h);
				void				draw();
				void				step(double const & time, double const & dt);
				/** @} */

				template<class Archive> void	serialize(Archive & ar, unsigned int const & version) {
					ar & boost::serialization::make_nvp("i",i_);
					ar & boost::serialization::make_nvp("flag",flag_);
					ar & boost::serialization::make_nvp("gravity",gravity_);
				}
			public:
				/** @todo replace types with inheritance */
				enum {
					NONE = 0,
					LOCAL,
					REMOTE
				};

				void						create_physics();
				/** @name Accessors @{ */
				physx::PxTransform				getPose();
				physx::PxTransform				getPoseGlobal();
				/** @} */
				/** @name Children @{ */
				/** @} */
				//void						create_actors(Neb::Scene::desc_w);
			private:	
				//_wNeb::Actor::Base>		create_actor(boost::shared_ptr<Neb::Actor::desc>);
			public:
				//Neb::weak_ptr<Neb::Actor::Base>			create_actor_local(Neb::Actor::desc_w);
				//Neb::weak_ptr<Neb::Actor::Base>			create_actor_remote(Neb::Actor::addr_w, Neb::Actor::desc_w);
				void							add_deferred(Neb::Actor::Base_s);

				virtual void						fire(Neb::Actor::Base_s) = 0;
				//void							send_actor_update();

				//int						recv(Neb::packet::packet);
				//void						read(Neb::active_transform::set*);
				//Neb::Scene::desc_s				desc_generate();

				virtual void						dumby() {}
			public:
				Neb::Scene::Util::Parent_w				parent_;

				// timer
				//gal::timer::timer_set			timer_set_;


				int							user_type_;
	
				physx::PxSimulationFilterShader				px_filter_shader_;

				Neb::simulation_callback*				simulation_callback_;

				physx::PxScene*						px_scene_;

				double							last_;

				//Neb::vehicle_manager					vehicle_manager_;

			public:
				Neb::Scene::Util::Flag					flag_;
				physx::PxVec3						gravity_;

				Neb::Scene::Util::Parent_w				renderable_;

				std::map<std::string, Neb::Actor::Base_s>		actors_deferred_;
		};
	}
}

#endif





