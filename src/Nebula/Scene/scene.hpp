#ifndef __GLUTPP_SCENE_H__
#define __GLUTPP_SCENE_H__

#include <vector>

#include <Nebula/Flag.hpp>
#include <Nebula/Map.hpp>

#include <Nebula/Types.hpp>
#include <Nebula/Scene/Types.hpp>

#include <Nebula/config.hpp> // Nebula/config.hpp.in
#include <Nebula/Graphics/glsl/program.hpp>
#include <Nebula/Scene/raw.hpp>
#include <Nebula/Actor/Base.hpp>
#include <Nebula/Graphics/Camera/View/Base.hpp>

//#include <glutpp/shader.h>

#define LIGHT_MAX 20

namespace Neb {
	namespace Scene {
		class scene: virtual public Neb::Actor::parent, public gal::flag {
			public:

				scene(Neb::Scene::Util::Parent_w);
				virtual ~scene();
				void				i(int ni);
				int				i();
				gal::flag::flag_type const &		f() const;
				void					f(unsigned int flag);
				void				init(Neb::Scene::desc_w desc);
				void				release();
				physx::PxMat44			get_pose();
				/** @brief render */
				void				render(
						double time,
						std::shared_ptr<Neb::Camera::View::Base>,
						std::shared_ptr<Neb::Camera::Projection::Base>,
						Neb::window::window_s);
				void				draw(Neb::window::window_s window);
				void				resize(int w, int h);



			public:
				/** @todo replace types with inheritance */
				enum {
					NONE = 0,
					LOCAL,
					REMOTE
				};

				void						create_physics();
				/** @name Accessors @{ */
				Neb::weak_ptr<Neb::app>				get_app();
				Neb::weak_ptr<Neb::Actor::Base>			get_actor(int i);
				Neb::weak_ptr<Neb::Actor::Base>			get_actor(Neb::Actor::addr_w);
				physx::PxTransform				getPose();
				physx::PxTransform				getPoseGlobal();
				/** @} */

				void						create_actors(Neb::Scene::desc_w);
			private:	
				//_wNeb::Actor::Base>		create_actor(boost::shared_ptr<Neb::Actor::desc>);
			public:
				//Neb::weak_ptr<Neb::Actor::Base>			create_actor_local(Neb::Actor::desc_w);
				//Neb::weak_ptr<Neb::Actor::Base>			create_actor_remote(Neb::Actor::addr_w, Neb::Actor::desc_w);
				//void						add_deferred(Neb::Actor::desc_w);

				/** @name Main Loop @{ */
				void						draw();
				void						step(double);
				void						step_local(double);
				void						step_remote(double);
				/** @} */

				void						fire(Neb::Actor::Base_w);
				void						fire_local(Neb::Actor::Base_w);
				void						fire_remote(Neb::Actor::Base_w);



				// networking
				void						send_actor_update();

				//int						recv(Neb::packet::packet);
				//void						read(Neb::active_transform::set*);
				//Neb::Scene::desc_s				desc_generate();

				virtual void					dumby() {}
			public:
				Neb::app_w					app_;

				// timer
				//gal::timer::timer_set			timer_set_;


				int						user_type_;
	
				physx::PxSimulationFilterShader			px_filter_shader_;

				Neb::simulation_callback*			simulation_callback_;

				physx::PxScene*					px_scene_;

				double							last_;

				//Neb::vehicle_manager					vehicle_manager_;

			public:
				int							i_;
				raw_s							raw_;
				
				Neb::weak_ptr<Neb::renderable>				renderable_;

				Neb::Map<Neb::Actor::Base>				actors_;
				std::map<std::string, Neb::Actor::Base_s>		actors_deferred_;
		};
	}
}

#endif





