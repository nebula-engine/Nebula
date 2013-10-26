#ifndef __NEBULA_CONTENT_ACTOR_ADMIN_RIGID_BODY_HPP__
#define __NEBULA_CONTENT_ACTOR_ADMIN_RIGID_BODY_HPP__



#include <nebula/content/actor/admin/rigid_actor.hpp>

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
				class rigid_body:
					public nebula::content::actor::admin::rigid_actor
				{
					protected:
						/** \brief copy ctor
						*/
						rigid_body( rigid_body const & ) = default;
						/** \brief assignment
						*/
						rigid_body&						operator=( rigid_body const & ) = default;
						/** \brief ctor
						*/
						rigid_body( n32100::base::shared_t );
					public:
						/** \brief dtor
						*/
						~rigid_body();
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
						/** \briefcreate shape
						*/
						virtual void						create_shapes();
				};
			}
		}
	}
}

#endif








