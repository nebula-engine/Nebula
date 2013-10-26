#ifndef __NEBULA_CONTENT_ACTOR_ADMIN_RIGID_STATIC_PLANE_HPP__
#define __NEBULA_CONTENT_ACTOR_ADMIN_RIGID_STATIC_PLANE_HPP__

#include <nebula/content/actor/admin/rigid_static.hpp>

namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace admin
			{
				/** \brief rigid static plane
				*/
				class rigid_static_plane:
					public nebula::content::actor::admin::rigid_static
				{
					protected:
						/** \brief copy ctor
						*/
						rigid_static_plane( rigid_static_plane const & ) = default;
						/** \brief assignment
						*/
						rigid_static_plane&				operator=( rigid_static_plane const & ) = default;
						/** \brief ctor
						*/
						rigid_static_plane( n32100::base::shared_t ) = default;
					public:
						/** \brief dtor
						*/
						~rigid_static_plane();
						/** \brief init
						*/
						virtual	void					init();
						/** \brief shutdown
						*/
						virtual	void					shutdown();
						/** \brief update
						*/
						virtual	void					update();
						/** \brief step
						*/
						virtual	void					step( float );
						/** \brief render
						*/
						virtual	void					render( n23000::base::shared_t );
						/** \brief create shapes
						*/
						virtual	void					create_shapes();
					protected:
						/** \brief plane
						*/
						n35100::plane::shared_t				plane_;
				};
			}
		}
	}
}


#endif








