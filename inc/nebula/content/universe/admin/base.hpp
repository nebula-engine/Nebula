#ifndef __NEBULA_CONTENT_UNIVERSE_ADMIN_BASE_HPP__
#define __NEBULA_CONTENT_UNIVERSE_ADMIN_BASE_HPP__

#include <jess/shared_ptr.hpp>
#include <jess/ostream.hpp>
#include <jess/map.hpp>

#include <nebula/content/base.hpp>
#include <nebula/define.hpp>
#include <nebula/ns.hpp>

namespace nebula
{
	namespace content
	{
		namespace universe
		{
			namespace admin
			{
				class base:
					public jess::enable_shared_from_this<n31100::base>
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
						base( jess::shared_ptr<n30000::base> );
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
						/** \brief request window
						*/
						virtual jess::shared_ptr<n22000::base>			request_window();
						/** \brief create scene
						*/
						template <class T> jess::shared_ptr<T>			create_scene()
						{
							jess::clog << NEB_FUNCSIG << std::endl;

							jess::shared_ptr<T> t = parent_.lock()->create_scene<T>( shared_from_this() );

							scenes_.push<T>( t );

							return t;
						}
						/** rigid dynamic box
						*/
						virtual n34100::rigid_dynamic_box::shared_t	create_rigid_dynamic_box( n32100::base::shared_t );
						/** rigid static plane
						*/
						virtual n34100::rigid_static_plane::shared_t	create_rigid_static_plane( n32100::base::shared_t );
						/** controller
						*/
						virtual n34100::controller::base::shared_t	create_controller( n32100::base::shared_t );
						/** physics material
						*/
						n34200::material::shared_t			request_material_physics();
						/** plane
						*/
						virtual n35100::plane::shared_t			create_plane( jess::shared_ptr<n34100::rigid_actor> );
						/** box
						*/
						virtual n35100::box::shared_t			create_box( jess::shared_ptr<n34100::rigid_actor> );
					public:
						/** \brief parent
						*/
						n30000::base::weak_t				parent_;
						/** \brief scenes
						*/
						jess::map<n32100::base>				scenes_;
				};
			}
		}
	}
}




#endif
