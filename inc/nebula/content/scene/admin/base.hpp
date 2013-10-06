#ifndef __NEBULA_CONTENT_SCENE_ADMIN_BASE_HPP__
#define __NEBULA_CONTENT_SCENE_ADMIN_BASE_HPP__

#include <ctime>

#include <jess/shared_ptr.hpp>
#include <jess/map.hpp>

#include <nebula/define.hpp>
#include <nebula/utilities/types/platform/types.hpp>
#include <nebula/utilities/types/content/types.hpp>
#include <nebula/utilities/types/content/scene/types.hpp>
#include <nebula/utilities/types/content/universe/types.hpp>
#include <nebula/utilities/types/content/view/types.hpp>
#include <nebula/utilities/types/content/actor/types.hpp>
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
				* \todo Create trigger object (might need to go in physics). Need to see if PhysX already has an object/functionality for this.
				*/
				class base:
					public jess::enable_shared_from_this<nc_sc_a::base>
				{
				public:
					/// ctor
					base();
					/// dtor
					~base();
					/// init
					virtual void									init( jess::shared_ptr<ncua::base>& );
					/// shutdown
					virtual void									shutdown();
					/// update
					virtual void									update();
					/// step
					virtual void									step( FLOAT dt );
					/// render
					virtual void									render( jess::shared_ptr<npr::base>& );
					/// get content
					jess::shared_ptr<nc::base>							get_content();
					/// request window
					virtual void									request_window( jess::shared_ptr<npw::base>& );				
					/// create
					virtual void									create_rigid_dynamic_box( jess::shared_ptr<ncaa::rigid_dynamic_box>& );
					/// get rid of this
					virtual void									register_rigid_dynamic( jess::shared_ptr<ncaa::rigid_dynamic> );
					/// create
					template <class T> void								create_view( jess::shared_ptr<T>& t )
					{
						/// log
						jess::clog << NEB_FUNCSIG << std::endl;
						
						//void(*func)(jess::shared_ptr<nc_sc_a::base>&) = &T::init;
						
						views_.push<T>( t, std::bind( &T::init, std::placeholders::_1, shared_from_this() ) );
					}
					/// create
					virtual void									create_controller( jess::shared_ptr<ncaa::controller>& );			
					/// parent
					std::weak_ptr<ncua::base>							parent_;
					/// time of last update
					std::time_t									last_;
					/// now
					std::time_t									now_;
					/// step size
					FLOAT										step_size_;
					/// accumulated time (replace with accumulator object)
					FLOAT										accumulator_;
					///@name children
					///@{
					/// physics
					jess::shared_ptr<nc_sc_p::base>							physics_;
					/// renderer
					jess::shared_ptr<nc_sc_r::base>							renderer_;
					/// views
					jess::map<ncva::base>								views_;
					/// actors
					jess::map<ncaa::base>								actors_;
					///@}
				};
			}
		}
	}
}


#endif
