#ifndef __NEBULA_CONTENT_ACTOR_ADMIN_BASE_HPP__
#define __NEBULA_CONTENT_ACTOR_ADMIN_BASE_HPP__

#include <nebula/define.hpp>
#include <PxPhysicsAPI.h>

#include <jess/shared_ptr.hpp>
#include <jess/map.hpp>

#include <nebula/content/scene/admin/base.hpp>

#include <nebula/ns.hpp>

namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace admin
			{
				/** \brief base
				 */
				class base:
					public std::enable_shared_from_this<n34100::base>
				{
					public:
						friend class n36000::base;
						friend class n32200::base;
					protected:
						/** \brief copy ctor
						 */
						base( base const & ) = default;
						/** \brief assignment
						 */
						base&							operator=( base const & ) = default;
					public:
						/** \brief ctor
						 */
						base( jess::shared_ptr<n32100::base> );
						/** \brief dtor
						 */
						virtual ~base();
						/** \brief init
						 */
						virtual	void						init();
						/** \brief shutdown
						 */
						virtual	void						shutdown();
						/** \brief update
						 */
						virtual	void						update();
						/** \brief step
						 */
						virtual	void						step( float );
						/** \brief render
						 */
						virtual	void						render( jess::shared_ptr<n23000::base> );
						/** \brief material physics
						 */
						virtual jess::shared_ptr<n34200::material>		create_physics_material();
						/** \brief create shapes
						 */
						virtual	void						create_shapes();
					protected:
						/** \brief parent
						 */
						std::weak_ptr<n32100::base>					parent_;
						/** \brief physics
						 */
						std::shared_ptr<n34200::base>					physics_;
						/** \brief renderer
						 */
						std::shared_ptr<n34300::base>					renderer_;
						/** \brief control
						 */
						std::shared_ptr<n34400::base>					control_;
						/** \brief materials
						 */
						jess::map<n34100::material>				materials_;
						/** \brief flag
						 */
						unsigned int						flag_;
						/** \brief pose
						 */
						physx::PxMat44						pose_;
				};
			}
		}
	}
}

#endif








