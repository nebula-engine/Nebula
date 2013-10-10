#ifndef __NEBULA_CONTENT_SCENE_PHYSICS_PHYSX_BASE_HPP__
#define __NEBULA_CONTENT_SCENE_PHYSICS_PHYSX_BASE_HPP__

#include <jess/shared_ptr.hpp>

#include <nebula/define.hpp>

#include <PxPhysicsAPI.h>

#include <nebula/content/scene/physics/base.hpp>

#include <nebula/ns.hpp>

namespace nebula
{
	namespace content
	{
		namespace scene
		{
			namespace physics
			{
				namespace physx
				{
					class base:
						public nc_sc_p::base
					{
					public:
						base();
						virtual ~base();
						base(const base&);
						base&									operator=(const base&);
						/// init
						void									init( jess::shared_ptr<nc_sc_a::base> );
						void									shutdown();
						void									step(FLOAT);
						
						
						void									customize_scene_desc( ::physx::PxSceneDesc& );
						void									add_actor( jess::shared_ptr<ncaa::actor> act );
						
						
						::physx::PxScene*							get_px_scene();

						::physx::PxScene*							px_scene_;
							


						::physx::PxSimulationFilterShader					px_default_filter_shader_;
						
					};

				}
			}
		}
	}
}

#endif
