#ifndef __NEBULA_CONTENT_BASE_HPP__
#define __NEBULA_CONTENT_BASE_HPP__

#include <jess/map.hpp>
#include <jess/scoped_ostream.hpp>

#include <nebula/define.hpp>
#include <nebula/content/physics/base.hpp>

#include <nebula/ns.hpp>

namespace nebula
{
	namespace content
	{
		class base:
			public std::enable_shared_from_this<n30000::base>
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
				base( std::shared_ptr<n10000::app> );
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
				virtual std::shared_ptr<n22000::base>				request_window();
				///@name create
				///@{
				/**
				*/
				/** \brief universe
				*/
				template <class T> std::shared_ptr<T>				create_universe()
				{
					jess::clog << NEB_FUNCSIG << std::endl;

					std::shared_ptr<T> t( new T( shared_from_this() ) );				

					universes_.push<T>( t );

					t->init();

					return t;
				}
				/** \brief scene
				*/
				template <class T> std::shared_ptr<T>				create_scene( std::shared_ptr<n31100::base> universe )
				{
					jess::scoped_ostream( &jess::clog, NEB_FUNCSIG );
					
					std::shared_ptr<T> scene( new T( universe ) );
					
					scene->physics_ = physics_->create_scene( scene );
					
					scene->init();

					return scene;
				}
				/** \brief rigid dynamic box
				*/
				virtual std::shared_ptr<n34100::rigid_dynamic_box>		create_rigid_dynamic_box(
						std::shared_ptr<n32100::base>
						//std::shared_ptr<n34100::base>
						);
				/** \brief rigid static plane
				*/
				virtual std::shared_ptr<n34100::rigid_static_plane>		create_rigid_static_plane(
						std::shared_ptr<n32100::base>
						//std::shared_ptr<n34100::base>
						);
				/** \brief controller
				*/
				virtual std::shared_ptr<n34100::controller::base>		create_controller(
						std::shared_ptr<n32100::base>
						//std::shared_ptr<n34100::base>
						);
				/** box
				*/
				virtual std::shared_ptr<n35100::box>				create_box( std::shared_ptr<n34100::rigid_actor> );
				/** plane
				*/
				virtual std::shared_ptr<n35100::plane>				create_plane( std::shared_ptr<n34100::rigid_actor> );
				///@}
				/** physics material
				*/
				std::shared_ptr<n34200::material>				request_physics_material();
			protected:
				/** \brief physics
				*/
				std::shared_ptr<n36000::base>					physics_;
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
