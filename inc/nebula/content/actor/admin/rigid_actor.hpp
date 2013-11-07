#ifndef __NEBULA_CONTENT_ACTOR_ADMIN_RIGID_ACTOR_HPP__
#define __NEBULA_CONTENT_ACTOR_ADMIN_RIGID_ACTOR_HPP__

#include <jess/map.hpp>

#include <nebula/content/actor/admin/actor.hpp>

#include <nebula/ns.hpp>

namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace admin
			{
				/// rigid dynamic
				class rigid_actor:
					public n34100::actor
				{
					protected:
						/** \brief copy ctor
						*/
						rigid_actor( rigid_actor const & ) = default;
						/** \brief assignment
						*/
						rigid_actor&						operator=( rigid_actor const & ) = default;
						/** \brief ctor
						*/
						rigid_actor( std::shared_ptr<n32100::base> );
					public:
						/** \brief dtor
						*/
						~rigid_actor();
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
						virtual	void						render( std::shared_ptr<n23000::base> );
						/** \brief create shapes
						*/
						virtual	void						create_shapes();
						/** \brief create box
						*/
						//virtual std::shared_ptr<n35100::box>			create_box();
						/** \brief create plane
						*/
						//virtual std::shared_ptr<n35100::plane>			create_plane();
						/** \brief shapes
						*/
						jess::map<n35100::base>					shapes_;
				};
			}
		}
	}
}

#endif








