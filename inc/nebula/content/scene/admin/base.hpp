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
				/// base
				/*
				 * \todo Create trigger object (might need to go in physics). Need to see if PhysX already has an object/fun30000tionality for this.
				 */
				class base:
					public jess::enable_shared_from_this<n32100::base>
				{
					public:
						/// ctor
						base();
						/// dtor
						~base();
						/// init
						virtual void									init( jess::shared_ptr<n31100::base> );
						/// shutdown
						virtual void									shutdown();
						/// update
						virtual void									update();
						/// step
						virtual void									step( float dt );
						/// render
						virtual void									render( jess::shared_ptr<n23000::base> );
						/// get content
						jess::shared_ptr<n30000::base>							get_content();
						/// request window
						virtual jess::shared_ptr<n22000::base>						request_window();
						/// create
						virtual jess::shared_ptr<n34100::rigid_dynamic_box>				create_rigid_dynamic_box();
						/// create
						virtual jess::shared_ptr<n34100::controller>					create_controller();
						/// create
						//virtual jess::shared_ptr<n34200::rigid_dynamic_box>				create_physics_rigid_dynamic_box();
						/// create
						//virtual jess::shared_ptr<n34200::controller>					create_physics_controller();




						/// get rid of this
						//virtual void									register_rigid_dynamic( jess::shared_ptr<n34100::rigid_dynamic> );
						/// create
						template <class T> jess::shared_ptr<T>						create_view()
						{
							/// log
							jess::clog << NEB_FUNCSIG << std::endl;

							jess::shared_ptr<T> t( new T );

							//void(*fun30000)(jess::shared_ptr<n32100::base>&) = &T::init;

							views_.push<T>( t );//, std::bind( &T::init, std::placeholders::_1, shared_from_this() ) );

							t->init( shared_from_this() );

							return t;
						}
						/// physics material
						jess::shared_ptr<n34200::material>						request_physics_material();




					public:
						/// parent
						std::weak_ptr<n31100::base>							parent_;
						/// time of last update
						std::time_t									last_;
						/// now
						std::time_t									now_;
						/// step size
						float										step_size_;
						/// accumulated time (replace with accumulator object)
						float										accumulator_;
						///@name children
						///@{
						/// physics
						jess::shared_ptr<n32200::base>							physics_;
						/// renderer
						jess::shared_ptr<n32300::base>							renderer_;
						/// views
						jess::map<n33100::base>								views_;
						/// actors
						jess::map<n34100::base>								actors_;
						///@}
				};
			}
		}
	}
}


#endif
