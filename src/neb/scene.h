#ifndef _NEBULA_CONTENT_SCENE_PHYSICS_BASE_HPP__
#define _NEBULA_CONTENT_SCENE_PHYSICS_BASE_HPP__

#include <memory>
#include <vector>

#include <PxPhysicsAPI.h>

#include <neb/actor/Rigid_Dynamic_Box.h>
#include <neb/actor/Rigid_Static_Plane.h>
#include <neb/actor/Controller.h>
#include <neb/actor/Light.h>

#include <tinyxml/tinyxml.h>

namespace neb
{
	class scene
	{
		public:
			scene();
			void		Create_Actors(TiXmlElement*);
			void		Create_Actor(TiXmlElement*);


			neb::actor::Rigid_Dynamic_Box*			Create_Rigid_Dynamic_Box(TiXmlElement*);
			neb::actor::Rigid_Static_Plane*			Create_Rigid_Static_Plane(TiXmlElement*);
			std::shared_ptr<neb::actor::Controller>		Create_Controller(TiXmlElement*);
			neb::actor::Light*				Create_Light(TiXmlElement*);
	
			void						Display();
			void						Step(float);


			physx::PxSimulationFilterShader			px_filter_shader_;

			std::vector<neb::actor::Base*>			actors_;
			std::vector<neb::actor::Light*>			lights_;

			physx::PxScene*					px_scene_;



	};
}

#endif



