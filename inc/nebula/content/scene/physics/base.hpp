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
					protected:
						/** \brief copy ctor
						*/
						base( basen const & ) = default;
						/** \brief assignment
						*/
						base&							operator=( base const & ) = default;
					public:
						/** \brief dtor
						*/
						virtual ~base();
						/** \brief init
						*/
						virtual void						init( jess::shared_ptr<n32100::base> );
						/** \brief shutdown
						*/
						virtual void						shutdown();
						/** \brief update
						*/
						virtual void						update();
						/** \brief step
						*/
						virtual void						step( float );
						/** \brief render
						*/
						virtual void						render( jess::shared_ptr<n23000::base> );
						/** \brief customize scene description
						*/
						virtual void						customize_scene_desc( physx::PxSceneDesc& );
					public:
						/** \brief parent
						*/
						std::weak_ptr<n32100::base>				parent_;
						/** \brief PxScene
						*/
						physx::PxScene*						px_scene_;
						/** \brief simulation filter shader
						*/
						physx::PxSimulationFilterShader				px_default_filter_shader_;
				};
			}
		}
	}
}

#endif
