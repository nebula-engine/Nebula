#ifndef __NEBULA_CONTENT_UNIVERSE_ADMIN_BASE_HPP__
#define __NEBULA_CONTENT_UNIVERSE_ADMIN_BASE_HPP__

#include <jess/ostream.hpp>
#include <jess/map.hpp>

#include <ker/module/module.hpp>

#include <nebula/define.hpp>
#include <nebula/ns.hpp>
#include <nebula/content/base.hpp>

namespace nebula
{
	namespace content
	{
		namespace universe
		{
			namespace admin
			{
				class base:
					public ker::module::module
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
						base();
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
						//virtual std::shared_ptr<n22000::base>			request_window();
						/** \brief create scene
						*/
						/*std::shared_ptr<ker::module::module>			create_scene()
						{
							jess::clog << NEB_FUNCSIG << std::endl;

							std::shared_ptr<T> t = parent_.lock()->create_scene<T>( shared_from_this() );

							scenes_.push<T>( t );

							return t;
						}*/
						/** rigid dynamic box
						*/
						//virtual std::shared_ptr<ker::module::module>		create_rigid_dynamic_box( std::shared_ptr<ker::module::module> );
						/** rigid static plane
						*/
						//virtual std::shared_ptr<ker::module::module>		create_rigid_static_plane( std::shared_ptr<ker::module::module> );
						/** controller
						*/
						//virtual std::shared_ptr<ker::module::module>		create_controller( std::shared_ptr<ker::module::module> );
						/** physics material
						*/
						//std::shared_ptr<n34200::material>			request_material_physics();
						/** plane
						*/
						//virtual std::shared_ptr<n35100::plane>			create_plane( std::shared_ptr<n34100::rigid_actor> );
						/** box
						*/
						//virtual std::shared_ptr<n35100::box>			create_box( std::shared_ptr<n34100::rigid_actor> );
					public:
						/** \brief parent
						*/
						std::weak_ptr<n30000::base>				parent_;
						/** \brief scenes
						*/
						jess::map<n32100::base>					scenes_;
				};
			}
		}
	}
}




#endif
