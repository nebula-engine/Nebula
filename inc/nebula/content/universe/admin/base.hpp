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
					public:
						/// ctor
						base( jess::shared_ptr<n30000::base> );
						/// dtor
						virtual ~base();
						/// init
						virtual void						init();
						/// shutdown
						virtual void						shutdown();
						/// update
						virtual void						update();
						/// request window
						virtual jess::shared_ptr<n22000::base>			request_window();
						/// create scene
						template <class T> jess::shared_ptr<T>			create_scene()
						{
							jess::clog << NEB_FUNCSIG << std::endl;

							jess::shared_ptr<T> t = parent_.lock()->create_scene<T>( shared_from_this() );//<-- no matching function!!!

							scenes_.push<T>( t );

							return t;
						}
						/// rigid dynamic box
						virtual jess::shared_ptr<n34100::rigid_dynamic_box>	create_rigid_dynamic_box( jess::shared_ptr<n32100::base> );
						/// rigid static plane
						virtual jess::shared_ptr<n34100::rigid_static_plane>	create_rigid_static_plane( jess::shared_ptr<n32100::base> );
						/// controller
						virtual jess::shared_ptr<n34100::controller>		create_controller( jess::shared_ptr<n32100::base> );
						/// physics material
						jess::shared_ptr<n34200::material>			request_physics_material();
					public:
						/// parent
						std::weak_ptr<n30000::base>			parent_;
						/// scenes
						jess::map<n32100::base>					scenes_;
				};
			}
		}
	}
}




#endif
