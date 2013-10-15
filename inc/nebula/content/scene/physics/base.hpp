#ifndef _NEBULA_CONTENT_SCENE_PHYSICS_BASE_HPP__
#define _NEBULA_CONTENT_SCENE_PHYSICS_BASE_HPP__

#include <nebula/define.hpp>
#include <PxPhysicsAPI.h>

#include <jess/shared_ptr.hpp>

#include <nebula/ns.hpp>

namespace nebula
{
	namespace content
	{
		namespace scene
		{
			namespace physics
			{
				class base
				{
					public:

						base();

						virtual ~base();

						base(const base&);

						base&							operator=(const base&);

						virtual void						init( jess::shared_ptr<n32100::base> );

						virtual void						shutdown();

						virtual void						update();

						virtual void						step(float);

						virtual void						render( jess::shared_ptr<n23000::base> );

						//virtual jess::shared_ptr<n34200::rigid_dynamic_box>	create_rigid_dynamic_box();
						/// controller
						//virtual jess::shared_ptr<n34200::controller>		create_controller();

						//virtual void						register_actor( jess::shared_ptr<n34100::actor> );

						virtual void						customize_scene_desc( physx::PxSceneDesc& );
					public:

						std::weak_ptr<n32100::base>				parent_;
						
						physx::PxScene*						get_px_scene();

						physx::PxScene*						px_scene_;

						physx::PxSimulationFilterShader				px_default_filter_shader_;
				};
			}
		}
	}
}

#endif
