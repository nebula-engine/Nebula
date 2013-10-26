#ifndef __NEBULA_CONTENT_ACTOR_ADMIN_BASE_HPP__
#define __NEBULA_CONTENT_ACTOR_ADMIN_BASE_HPP__

#include <nebula/define.hpp>
#include <PxPhysicsAPI.h>

#include <jess/shared_ptr.hpp>
#include <jess/map.hpp>

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
					public jess::enable_shared_from_this<n34100::base>
				{
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
						n32100::base::weak_t					parent_;
						/** \brief physics
						*/
						n34200::base::shared_t					physics_;
						/** \brief renderer
						*/
						n34300::base::shared_t					renderer_;
						/** \brief control
						*/
						n34400::base::shared_t					control_;
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








