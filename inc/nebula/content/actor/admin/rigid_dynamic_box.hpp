#ifndef __NEBULA_CONTENT_ACTOR_ADMIN_RIGID_DYNAMIC_BOX_HPP__
#define __NEBULA_CONTENT_ACTOR_ADMIN_RIGID_DYNAMIC_BOX_HPP__

#include <nebula/content/actor/admin/rigid_dynamic.hpp>

#include <nebula/ns.hpp>

namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace admin
			{
				/** \brief rigid dynamic
				*/
				class rigid_dynamic_box:
					public n34100::rigid_dynamic
				{
					public:
						typedef std::shared_ptr<rigid_dynamic_box>			shared_t;
					protected:
						/** \brief copy ctor
						*/
						rigid_dynamic_box(const rigid_dynamic_box&);
						/** \brief assignment
						*/
						rigid_dynamic_box&					operator=(const rigid_dynamic_box&);
						/** \brief actor
						*/
						rigid_dynamic_box( jess::shared_ptr<n32100::base> );
					public:
						/** \brief dtor
						*/
						~rigid_dynamic_box();
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
						/** \brief create shapes
						*/
						virtual	void						create_shapes();
						/** \brief shape
						*/
						jess::shared_ptr<n35100::box>				box_;
						/** \brief size
						*/
						physx::PxVec3						size_;
				};
			}
		}
	}
}

#endif








