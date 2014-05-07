#ifndef _NEBULA_CONTENT_SCENE_PHYSICS_BASE_HPP__
#define _NEBULA_CONTENT_SCENE_PHYSICS_BASE_HPP__

#include <memory>
#include <vector>

#include <PxPhysicsAPI.h>

//#include <galaxy/map.hpp>
//#include <galaxy/network/message.hpp>
//#include <galaxy/timer/timer_set.hpp>

#include <gru/config.hpp>
#include <gru/scene/scene.hpp>
#include <gru/Graphics/light/desc.hpp>

#include <nebula/config.hpp>
//#include <nebula/scene/desc.hpp>
#include <nebula/vehicle_manager.hpp>
#include <nebula/actor/Rigid_Dynamic.hpp>
#include <nebula/actor/Rigid_Static.hpp>
#include <nebula/actor/Controller.hpp>

#include <tinyxml2.h>

//int			parse_shape_type(char const * str);
//neb::shape::shape	xml_parse_geo(tinyxml2::XMLElement* element);

namespace neb {
	namespace scene {
		class scene: public glutpp::scene::scene {
			public:
				/** @todo replace types with inheritance */
				enum {
					NONE = 0,
					LOCAL,
					REMOTE
				};

				scene(neb::app_s);
				void						init(boost::shared_ptr<glutpp::scene::desc>);
				void						create_physics();
				/** @name Accessors @{ */
				Neb::weak_ptr<neb::app>				get_app();
				Neb::weak_ptr<neb::Actor::Base>			get_actor(int i);
				Neb::weak_ptr<neb::Actor::Base>			get_actor(boost::shared_ptr<glutpp::actor::addr>);
				physx::PxMat44					getPose();
				physx::PxMat44					getPoseGlobal();
				/** @} */

				void						create_actors(boost::shared_ptr<glutpp::scene::desc>);
			private:	
				boost::shared_ptr<neb::Actor::Base>		create_actor(boost::shared_ptr<glutpp::actor::desc>);
			public:
				Neb::weak_ptr<neb::Actor::Base>			create_actor_local(boost::shared_ptr<glutpp::actor::desc>);
				Neb::weak_ptr<neb::Actor::Base>			create_actor_remote(boost::shared_ptr<glutpp::actor::addr>, boost::shared_ptr<glutpp::actor::desc>);
				void						add_deferred(boost::shared_ptr<glutpp::actor::desc>);

				/** @name Main Loop @{ */
				void						draw();
				void						step(double);
				void						step_local(double);
				void						step_remote(double);
				/** @} */

				void						fire(neb::Actor::Base_s);
				void						fire_local(neb::Actor::Base_s);
				void						fire_remote(neb::Actor::Base_s);



				// networking
				void					send_actor_update();

				//int					recv(neb::packet::packet);
				//void					read(neb::active_transform::set*);
				//glutpp::scene::desc_s			desc_generate();

				virtual void				dumby() {}
			public:
				neb::app_w				app_;

				// timer
				//gal::timer::timer_set			timer_set_;

				int					user_type_;

				physx::PxSimulationFilterShader		px_filter_shader_;

				neb::simulation_callback*		simulation_callback_;

				physx::PxScene*				px_scene_;

				double					last_;

				//neb::vehicle_manager			vehicle_manager_;
		};
	}
}

#endif



