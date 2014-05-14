#ifndef __GLUTPP_SCENE_H__
#define __GLUTPP_SCENE_H__

#include <vector>

#include <Nebula/Flag.hh>
#include <Nebula/Util/Map.hh>

#include <Nebula/Types.hh>

#include <Nebula/Scene/Util/Types.hh>

#include <Nebula/config.hh> // Nebula/config.hpp.in
#include <Nebula/Graphics/glsl/program.hh>


#include <Nebula/Actor/Base.hh>
#include <Nebula/Graphics/Camera/View/Base.hh>

//#include <glutpp/shader.h>

#define LIGHT_MAX 20

namespace Neb {
	namespace Scene {
		class Base:
			virtual public Neb::Actor::Util::Parent,
			public gal::flag
		{
			public:

				Base(Neb::Scene::Util::Parent_w);
				virtual ~Base();
				void				i(int ni);
				int				i();
				gal::flag::flag_type const &		f() const;
				void					f(unsigned int flag);
				//void				init(Neb::Scene::desc_w desc);
				void				release();
				physx::PxMat44			get_pose();
				/** @name Main Loop @{ */
				/** @brief render */
				void				render(
						double time,
						std::shared_ptr<Neb::Camera::View::Base>,
						std::shared_ptr<Neb::Camera::Projection::Base>,
						Neb::Graphics::Window::Base_s);
				void				draw(Neb::Graphics::Window::Base_s window);
				void				resize(int w, int h);
				void				draw();
				void				step(double);
				/** @} */


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

				//void						create_actors(Neb::Scene::desc_w);
			private:	
				//_wNeb::Actor::Base>		create_actor(boost::shared_ptr<Neb::Actor::desc>);
			public:
				//Neb::weak_ptr<Neb::Actor::Base>			create_actor_local(Neb::Actor::desc_w);
				//Neb::weak_ptr<Neb::Actor::Base>			create_actor_remote(Neb::Actor::addr_w, Neb::Actor::desc_w);
				//void						add_deferred(Neb::Actor::desc_w);

				
				

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
				Neb::Scene::Util::Parent_w			parent_;

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
				unsigned int						flag_;
				physx::PxVec3						gravity_;

				Neb::Scene::Util::Parent_w				renderable_;

				Neb::Map<Neb::Actor::Base>				actors_;
				std::map<std::string, Neb::Actor::Base_s>		actors_deferred_;
		};
		class Local: public Neb::Scene::Base {

		};
		class Remote: public Neb::Scene::Base {

		};
	}
}

#endif





