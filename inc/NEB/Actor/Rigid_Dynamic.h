#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_DYNAMIC_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_DYNAMIC_HPP__

#include <NEB/Actor/Rigid_Body.h>

namespace NEB
{
	namespace Actor
	{
		class Rigid_Dynamic:
			public NEB::Actor::Rigid_Body
		{
virtual void Display() = 0;
		};
	}
}

#endif








