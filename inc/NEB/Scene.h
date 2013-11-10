#ifndef _NEBULA_CONTENT_SCENE_PHYSICS_BASE_HPP__
#define _NEBULA_CONTENT_SCENE_PHYSICS_BASE_HPP__

#include <PxPhysicsAPI.h>

#include <NEB/Actor/Rigid_Dynamic_Box.h>

namespace NEB
{
	class Scene
	{
			public:
				NEB::Actor::Rigid_Dynamic_Box*		Create_Rigid_Dynamic_Box();
				
				
				physx::PxScene*				px_scene_;

				physx::PxSimulationFilterShader		px_default_filter_shader_;
		};
}

#endif
