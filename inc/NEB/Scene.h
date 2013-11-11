#ifndef _NEBULA_CONTENT_SCENE_PHYSICS_BASE_HPP__
#define _NEBULA_CONTENT_SCENE_PHYSICS_BASE_HPP__

#include <vector>

#include <PxPhysicsAPI.h>

#include <NEB/Actor/Rigid_Dynamic_Box.h>

namespace NEB
{
	class Scene
	{
		public:
			Scene();
			NEB::Actor::Rigid_Dynamic_Box*		Create_Rigid_Dynamic_Box();
			void					Display();

			std::vector<NEB::Actor::Base*>		actors_;


			physx::PxScene*				px_scene_;

			physx::PxSimulationFilterShader		px_default_filter_shader_;
	};
}

#endif
