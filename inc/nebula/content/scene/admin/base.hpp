#ifndef __NEBULA_CONTENT_SCENE_ADMIN_BASE_HPP__
#define __NEBULA_CONTENT_SCENE_ADMIN_BASE_HPP__

#include <ctime>

#include <jess/map.hpp>

#include <nebula/content/universe/admin/base.hpp>

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
					public ker::module::module
				{
					public:
						/** ctor
						*/
						base();
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
						virtual void							render( std::shared_ptr<n23000::base> );
						/** get content
						*/
						std::shared_ptr<n30000::base>					get_content();
						/** \brief controller to view
						*/
						void								connect_controller_to_view(
								std::shared_ptr<n34100::controller::base>,
								std::shared_ptr<n33100::base> );
						/** request window
						*/
						//virtual std::shared_ptr<n22000::base>					request_window();
						/** rigid dynamic box
						*/
						//virtual std::shared_ptr<n34100::rigid_dynamic_box>			create_rigid_dynamic_box();
						/** plane
						*/
						//virtual std::shared_ptr<n34100::rigid_static_plane>			create_rigid_static_plane();
						/** create
						*/
						//virtual std::shared_ptr<n34100::controller::base>			create_controller();
						/** box
						*/
						//virtual std::shared_ptr<n35100::box>					create_box(
						//		std::shared_ptr<n34100::rigid_actor> );
						/** plane
						*/
						//virtual std::shared_ptr<n35100::plane>					create_plane(
						//		std::shared_ptr<n34100::rigid_actor> );
						/** \brief create
						*/
						/*template <class T> std::shared_ptr<T>					create_view()
						{
							NEB_LOG_FUNC;
							
							return parent_.lock()->create_view<T>();
						}*/
						/** \brief physics material
						*/
						//std::shared_ptr<n34200::material>					request_material_physics();
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
						std::shared_ptr<n32200::base>					physics_;
						/** \brief renderer
						*/
						std::shared_ptr<n32300::base>					renderer_;
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
