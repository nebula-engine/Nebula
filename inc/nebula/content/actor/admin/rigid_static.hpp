#ifndef __NEBULA_CONTENT_ACTOR_ADMIN_RIGID_STATIC_HPP__
#define __NEBULA_CONTENT_ACTOR_ADMIN_RIGID_STATIC_HPP__

#include <nebula/content/actor/admin/rigid_actor.hpp>

namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace admin
			{
				/** \brief rigid static
				*/
				class rigid_static:
					public nebula::content::actor::admin::rigid_actor
				{
					protected:
						/** \brief copy ctor
						*/
						rigid_static( rigid_static const & );
						/** \brief assignment
						*/
						rigid_static&						operator=( rigid_static const & );
						/** \brief ctor
						*/
						rigid_static( std::shared_ptr<n32100::base>);
					protected:
						/** \brief dtor
						*/
						~rigid_static();
						/** \brief init
						*/
						virtual	void						init();
						/** \brief shutdown
						*/
						virtual	void						shutdown();
						/** \brief update
						*/
						virtual	void						update();
						/** \brief render
						*/
						virtual	void						render( std::shared_ptr<n23000::base> );
						/** \brief step
						*/
						virtual	void						step( float );
						/** \brief create shapes
						*/
						virtual	void						create_shapes();


				};
			}
		}
	}
}


#endif





