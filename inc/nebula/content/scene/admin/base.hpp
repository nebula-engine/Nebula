#ifndef __NEBULA_CONTENT_SCENE_ADMIN_BASE_HPP__
#define __NEBULA_CONTENT_SCENE_ADMIN_BASE_HPP__

#include <ctime>

#include <jess/shared_ptr.hpp>
#include <jess/map.hpp>

#include <nebula/define.hpp>
#include <nebula/ns.hpp>

namespace nebula
{
	namespace content
	{
		namespace scene
		{
			namespace admin
			{
				/** \brief base
				 *
				 * \todo Create trigger object (might need to go in physics).
				 * Need to see if PhysX already has an object functionality for this.
				 */
				class base:
					public jess::enable_shared_from_this<n32100::base>
				{
					public:
						/** ctor
						*/
						base( n31100::base::shared_t );
						/** dtor
						*/
						~base();
						/** init
						*/
						virtual void							init();
						/** shutdown
						*/
						virtual void							shutdown();
						/** update
						*/
						virtual void							update();
						/** step
						*/
						virtual void							step( float dt );
						/** render
						*/
						virtual void							render( n23000::base::shared_t );
						/** get content
						*/
						jess::shared_ptr<n30000::base>					get_content();
						/** \brief controller to view
						*/
						void								connect_controller_to_view(
								n34100::controller::base::shared_t,
								n33100::base::shared_t );
						/** request window
						*/
						virtual n22000::base::shared_t					request_window();
						/** rigid dynamic box
						*/
						virtual n34100::rigid_dynamic_box::shared_t			create_rigid_dynamic_box();
						/** plane
						*/
						virtual n34100::rigid_static_plane::shared_t			create_rigid_static_plane();
						/** create
						*/
						virtual n34100::controller::base::shared_t			create_controller();
						/** box
						*/
						virtual n35100::box::shared_t					create_box(
								n34100::rigid_actor::shared_t );
						/** plane
						*/
						virtual n35100::plane::shared_t					create_plane(
								n34100::rigid_actor::shared_t );
						/** \brief create
						*/
						template <class T> jess::shared_ptr<T>				create_view()
						{
							jess::clog << NEB_FUNCSIG << std::endl;

							jess::shared_ptr<T> t( new T );

							views_.push<T>( t );

							t->init( shared_from_this() );

							return t;
						}
						/** \brief physics material
						*/
						n34200::material::shared_t					request_material_physics();
					public:
						/** \brief parent
						*/
						std::weak_ptr<n31100::base>					parent_;
						/** \brief time of last update
						*/
						std::time_t							last_;
						/** \brief now
						*/
						std::time_t							now_;
						/** \brief step size
						*/
						float								step_size_;
						/** \brief accumulated time (replace with accumulator object)
						*/
						float								accumulator_;
						///@name children
						///@{
						/**
						*/
						/** \brief physics
						*/
						jess::shared_ptr<n32200::base>					physics_;
						/** \brief renderer
						*/
						jess::shared_ptr<n32300::base>					renderer_;
						/** \brief views
						*/
						jess::map<n33100::base>						views_;
						/** \brief actors
						*/
						jess::map<n34100::base>						actors_;
						///@}
				};
			}
		}
	}
}


#endif
