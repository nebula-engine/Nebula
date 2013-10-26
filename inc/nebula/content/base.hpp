#ifndef __NEBULA_CONTENT_BASE_HPP__
#define __NEBULA_CONTENT_BASE_HPP__

#include <jess/map.hpp>
#include <jess/shared_ptr.hpp>

#include <nebula/define.hpp>
#include <nebula/content/physics/base.hpp>

#include <nebula/ns.hpp>

namespace nebula
{
	namespace content
	{
		class base:
			public jess::enable_shared_from_this<n30000::base>
		{
			protected:
				/** \brief copy ctor
				*/
				base( base const & ) = default;
				/** \brief assignment
				*/
				base&								operator=( base const & ) = default;
			public:
				/** \brief ctor
				*/
				base( jess::shared_ptr<n10000::app> );
				/** \brief dtor
				*/
				virtual ~base();
				/** \brief init
				*/
				virtual void							init();
				/** \brief shutdown
				*/
				virtual void							shutdown();
				/** \brief update
				*/
				virtual void							update();
				/** \brief request window
				*/
				virtual jess::shared_ptr<n22000::base>				request_window();
				///@name create
				///@{
				/**
				*/
				/** \brief universe
				*/
				template <class T> jess::shared_ptr<T>				create_universe()
				{
					jess::clog << NEB_FUNCSIG << std::endl;

					jess::shared_ptr<T> t( new T( shared_from_this() ) );				

					universes_.push<T>( t );

					t->init();

					return t;
				}
				/** \brief scene
				*/
				template <class T> jess::shared_ptr<T>				create_scene( jess::shared_ptr<n31100::base> universe )
				{
					jess::clog << NEB_FUNCSIG << std::endl;

					jess::shared_ptr<T> t( new T( universe ) );

					t->physics_ = physics_->create_scene();

					t->init();

					return t;
				}
				/** \brief rigid dynamic box
				*/
				virtual jess::shared_ptr<n34100::rigid_dynamic_box>		create_rigid_dynamic_box(
						jess::shared_ptr<n32100::base>
						//jess::shared_ptr<n34100::base>
						);
				/** \brief rigid static plane
				*/
				virtual jess::shared_ptr<n34100::rigid_static_plane>		create_rigid_static_plane(
						jess::shared_ptr<n32100::base>
						//jess::shared_ptr<n34100::base>
						);
				/** \brief controller
				*/
				virtual jess::shared_ptr<n34100::controller::base>		create_controller(
						jess::shared_ptr<n32100::base>
						//jess::shared_ptr<n34100::base>
						);
				/** box
				*/
				virtual jess::shared_ptr<n35100::box>				create_box( jess::shared_ptr<n34100::rigid_actor> );
				/** plane
				*/
				virtual jess::shared_ptr<n35100::plane>				create_plane( jess::shared_ptr<n34100::rigid_actor> );
				///@}
				/** physics material
				*/
				jess::shared_ptr<n34200::material>				request_physics_material();
			protected:
				/** \brief physics
				*/
				jess::shared_ptr<n36000::base>					physics_;
				/** \brief universes
				*/
				jess::map<n31100::base>						universes_;
				/** \brief parent
				*/
				std::weak_ptr<n10000::app>					parent_;
		};
	}
}




#endif
