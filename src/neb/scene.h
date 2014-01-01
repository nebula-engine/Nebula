#ifndef _NEBULA_CONTENT_SCENE_PHYSICS_BASE_HPP__
#define _NEBULA_CONTENT_SCENE_PHYSICS_BASE_HPP__

#include <memory>
#include <vector>

#include <PxPhysicsAPI.h>

#include <gal/map.h>
#include <gal/network/message.h>

#include <glutpp/scene.h>
#include <glutpp/desc_light.h>

#include <neb/vehicle_manager.h>
#include <neb/actor/Rigid_Dynamic.h>
#include <neb/actor/Rigid_Static.h>
#include <neb/actor/Controller.h>
#include <neb/actor/Light.h>

#include <tinyxml2.h>

int		parse_shape_type(char const * str);
neb::shape	xml_parse_geo(tinyxml2::XMLElement* element);

namespace neb
{
	namespace actor
	{
		struct desc;
		class vehicle;
	}
	namespace packet
	{
		struct packet;
	}
	class simulation_callback;
	class scene: public glutpp::scene
	{
		public:
			typedef std::shared_ptr<neb::actor::Base>		base_t;
			typedef std::shared_ptr<neb::actor::Rigid_Dynamic>	rigid_dynamic_t;
			typedef std::shared_ptr<neb::actor::Rigid_Static>	rigid_static_t;
			typedef std::shared_ptr<neb::actor::Controller>		controller_t;
			typedef std::shared_ptr<neb::actor::Light>		light_t;
			typedef std::shared_ptr<neb::actor::vehicle>		vehicle_t;
			typedef std::shared_ptr<neb::app>			app_t;
			
			enum
			{
				NONE = 0,
				LOCAL,
				REMOTE
			};

			scene();
			app_t			get_app();
			
			void			create_actors(neb::actor::desc*, base_t = base_t());
			
			//base_t			Create_Actor(tinyxml2::XMLElement*, base_t);
			base_t			Create_Actor(neb::actor::desc*, base_t);
			
			rigid_dynamic_t		Create_Rigid_Dynamic(tinyxml2::XMLElement*, base_t);
			rigid_static_t		Create_Rigid_Static(tinyxml2::XMLElement*, base_t);
			rigid_static_t		Create_Rigid_Static_Plane(tinyxml2::XMLElement*, base_t);
			rigid_dynamic_t		Create_Rigid_Dynamic(neb::actor::desc*, base_t = base_t());
			rigid_static_t		Create_Rigid_Static(neb::actor::desc*, base_t);
			
			controller_t		Create_Controller(tinyxml2::XMLElement*);
			
			light_t			Create_Light(tinyxml2::XMLElement*, base_t);
			light_t			Create_Light(glutpp::desc_light, base_t);

			vehicle_t		create_vehicle();
			
			void					draw();

			void					step(double);
			void					step_local(double);
			void					step_remote(double);


			// networking
			neb::packet::packet			serialize();


			int					recv(neb::packet::packet);

		public:
			int					user_type_;

			physx::PxSimulationFilterShader		px_filter_shader_;
			
			neb::simulation_callback*		simulation_callback_;
			
			
			physx::PxScene*				px_scene_;
			
			std::weak_ptr<neb::app>			app_;
			double					last_;

	
			neb::vehicle_manager			vehicle_manager_;
	};
}

#endif



