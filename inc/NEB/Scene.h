#ifndef _NEBULA_CONTENT_SCENE_PHYSICS_BASE_HPP__
#define _NEBULA_CONTENT_SCENE_PHYSICS_BASE_HPP__

#include <memory>
#include <vector>

#include <PxPhysicsAPI.h>

#include <NEB/Actor/Rigid_Dynamic_Box.h>
#include <NEB/Actor/Rigid_Static_Plane.h>
#include <NEB/Actor/Controller.h>
#include <NEB/Actor/Light.h>

namespace NEB
{
	class Scene
	{
		public:
			Scene();
			void		Create_Actors(TiXmlElement*);
			void		Create_Actor(TiXmlElement*);


			NEB::Actor::Rigid_Dynamic_Box*		Create_Rigid_Dynamic_Box(TiXmlElement*);
			NEB::Actor::Rigid_Static_Plane*		Create_Rigid_Static_Plane(TiXmlElement*);
			std::shared_ptr<NEB::Actor::Controller>		Create_Controller(TiXmlElement*);
			NEB::Actor::Light*			Create_Light(TiXmlElement*);
	
			void					Display();
			void					Step(float);


			physx::PxSimulationFilterShader		px_filter_shader_;

			std::vector<NEB::Actor::Base*>		actors_;
			std::vector<NEB::Actor::Light*>		lights_;

			physx::PxScene*				px_scene_;



	};
}

#endif



