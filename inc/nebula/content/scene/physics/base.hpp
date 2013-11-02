#ifndef _NEBULA_CONTENT_SCENE_PHYSICS_BASE_HPP__
#define _NEBULA_CONTENT_SCENE_PHYSICS_BASE_HPP__

#include <nebula/define.hpp>
#include <PxPhysicsAPI.h>


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
						friend class n36000::base;
					protected:
						/** \brief copy ctor
						 */
						base( base const & ) = default;
						/** \brief assignment
						 */
						base&							operator=( base const & ) = default;
						/** \brief ctor
						 */
						base( std::shared_ptr<n32100::base> );
					public:
						/** \brief dtor
						 */
						virtual ~base();
						/** \brief init
						 */
						virtual void						init();
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
						virtual void						render( std::shared_ptr<n23000::base> );
						/** \brief customize scene description
						 */
						virtual void						customize_scene_desc( physx::PxSceneDesc& );
						virtual void						add( std::shared_ptr<n34100::rigid_dynamic_box> );
						virtual void						add( std::shared_ptr<n34100::rigid_static_plane> );
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
