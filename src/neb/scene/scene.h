#ifndef _NEBULA_CONTENT_SCENE_PHYSICS_BASE_HPP__
#define _NEBULA_CONTENT_SCENE_PHYSICS_BASE_HPP__

#include <memory>
#include <vector>

#include <PxPhysicsAPI.h>

#include <gal/map.h>
#include <gal/network/message.h>

#include <glutpp/config.h>
#include <glutpp/scene/scene.h>
#include <glutpp/light/desc.h>

#include <neb/config.h>
//#include <neb/scene/desc.h>
#include <neb/vehicle_manager.h>
#include <neb/actor/Rigid_Dynamic.h>
#include <neb/actor/Rigid_Static.h>
#include <neb/actor/Controller.h>

#include <tinyxml2.h>

int		parse_shape_type(char const * str);
neb::shape	xml_parse_geo(tinyxml2::XMLElement* element);

namespace neb
{
	namespace scene
	{
		class scene: public glutpp::scene::scene
		{
			public:
				typedef std::shared_ptr<neb::actor::Base>		base_t;
				typedef std::shared_ptr<neb::actor::Rigid_Dynamic>	rigid_dynamic_t;
				typedef std::shared_ptr<neb::actor::Rigid_Static>	rigid_static_t;
				typedef std::shared_ptr<neb::actor::Controller>		controller_t;
				typedef std::shared_ptr<neb::actor::vehicle>		vehicle_t;
				typedef std::shared_ptr<neb::app>			app_t;

				enum
				{
					NONE = 0,
					LOCAL,
					REMOTE
				};

				scene(neb::app_s);
				void			init(glutpp::scene::desc_s);
				void			create_physics();
				app_t			get_app();
				

				void			create_actors(glutpp::scene::desc_s);
			private:	
				base_t			create_actor(
						glutpp::actor::desc_s);
			public:
				base_t			create_actor_local(
						glutpp::actor::desc_s);

				base_t			create_actor_remote(
						glutpp::actor::addr_s,
						glutpp::actor::desc_s);

				//base_t			create_actor(glutpp::actor::desc*, base_t);

				/*			rigid_dynamic_t		Create_Rigid_Dynamic(
							neb::actor::desc*,
							base_t = base_t());

							rigid_static_t		Create_Rigid_Static(
							neb::actor::desc*,
							base_t);
				 */
				/*				rigid_static_t		Create_Rigid_Static_Plane(
								glutpp::actor::desc*,
								base_t);

								controller_t		Create_Controller(glutpp::actor::desc*);
								vehicle_t		create_vehicle();
				 */


				void					draw();

				void					step(double);
				void					step_local(double);
				void					step_remote(double);


				// networking
				void					send_actor_update();

				int					recv(neb::packet::packet);

				void					read(neb::active_transform::set*);

				glutpp::scene::desc_s		desc_generate();
			public:
				neb::app_w				app_;

				// timer
				gal::timer::timer_set			timer_set_;

				int					user_type_;

				physx::PxSimulationFilterShader		px_filter_shader_;

				neb::simulation_callback*		simulation_callback_;

				physx::PxScene*				px_scene_;

				double					last_;

				neb::vehicle_manager			vehicle_manager_;
		};
	}
}

#endif



