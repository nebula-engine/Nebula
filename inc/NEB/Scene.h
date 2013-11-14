#ifndef _NEBULA_CONTENT_SCENE_PHYSICS_BASE_HPP__
#define _NEBULA_CONTENT_SCENE_PHYSICS_BASE_HPP__

#include <vector>

#include <PxPhysicsAPI.h>

#include <NEB/Actor/Rigid_Dynamic_Box.h>
#include <NEB/Actor/Rigid_Static_Plane.h>
#include <NEB/Actor/Light.h>

namespace NEB
{
	class Scene
	{
		public:
			Scene();
			NEB::Actor::Rigid_Dynamic_Box*		Create_Rigid_Dynamic_Box();
			NEB::Actor::Rigid_Static_Plane*		Create_Rigid_Static_Plane();
			NEB::Actor::Light*			Create_Light();
	
			void					Display();
			void					Step(float);
			std::vector<NEB::Actor::Base*>		actors_;


			physx::PxScene*				px_scene_;

			physx::PxSimulationFilterShader		px_filter_shader_;
	};
}

#endif



