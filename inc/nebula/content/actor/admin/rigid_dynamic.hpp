#ifndef __NEBULA_CONTENT_ACTOR_ADMIN_RIGID_DYNAMIC_HPP__
#define __NEBULA_CONTENT_ACTOR_ADMIN_RIGID_DYNAMIC_HPP__

#include <nebula/content/actor/admin/rigid_body.hpp>

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
				class rigid_dynamic:
					public n34100::rigid_body
				{
					protected:
						/** \brief copy ctor
						*/
						rigid_dynamic(const rigid_dynamic&);
						/** \brief assignment
						*/
						rigid_dynamic&						operator=(const rigid_dynamic&);
						/** \brief ctor
						*/
						rigid_dynamic( n32100::base::shared_t );
					public:
						/** \brief dtor
						*/
						~rigid_dynamic();
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
						virtual	void						render( n23000::base::shared_t );
						/** \brief create shapes
						*/
						virtual	void						create_shapes();
				};
			}
		}
	}
}


#endif








