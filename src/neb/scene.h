#ifndef _NEBULA_CONTENT_SCENE_PHYSICS_BASE_HPP__
#define _NEBULA_CONTENT_SCENE_PHYSICS_BASE_HPP__

#include <memory>
#include <vector>

#include <PxPhysicsAPI.h>

#include <gal/map.h>

#include <glutpp/scene.h>

#include <neb/actor/Rigid_Dynamic.h>
#include <neb/actor/Rigid_Static.h>
#include <neb/actor/Controller.h>
#include <neb/actor/Light.h>

#include <tinyxml2.h>

int		parse_shape_type(char const * str);
neb::shape*	xml_parse_geo(tinyxml2::XMLElement* element);

namespace neb
{
	namespace actor
	{
		struct desc;
	}
	class simulation_callback;
	class view;
	class scene: public glutpp::scene
	{
		public:
			typedef std::shared_ptr<neb::actor::Base> rigid_dynamic_t;
			typedef std::shared_ptr<neb::actor::Rigid_Dynamic> rigid_dynamic_t;
			typedef std::shared_ptr<neb::actor::Rigid_Static> rigid_dynamic_t;
			
			
			enum
			{
				NONE = 0,
				LOCAL,
				REMOTE
			};
			scene();
			void		Create_Actors(tinyxml2::XMLElement*);
			void		Create_Actor(tinyxml2::XMLElement*);
			
			rigid_dynamic_t		Create_Rigid_Dynamic(tinyxml2::XMLElement*, );
			rigid_static_t		Create_Rigid_Static(tinyxml2::XMLElement*, );
			rigid_static_t		Create_Rigid_Static_Plane(tinyxml2::XMLElement*);
			std::shared_ptr<neb::actor::Rigid_Dynamic>	Create_Rigid_Dynamic(neb::actor::desc);
			std::shared_ptr<neb::actor::Rigid_Static>	Create_Rigid_Static(neb::actor::desc);

			std::shared_ptr<neb::actor::Controller>		Create_Controller(tinyxml2::XMLElement*);
			std::shared_ptr<neb::actor::Light>		Create_Light(tinyxml2::XMLElement*);

			void						draw();

			void						step(double);
			void						step_local(double);
			void						step_remote(double);

			int						remove_actor(int i);



			int						user_type_;

			physx::PxSimulationFilterShader			px_filter_shader_;
			
			neb::simulation_callback*			simulation_callback_;
			
			
			physx::PxScene*					px_scene_;
			
			std::weak_ptr<neb::app>				app_;
			std::weak_ptr<neb::view>			view_;
			double						last_;
	};
}

#endif



