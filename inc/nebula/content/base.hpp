#ifndef __NEBULA_CONTENT_BASE_HPP__
#define __NEBULA_CONTENT_BASE_HPP__

#include <jess/map.hpp>
#include <jess/shared_ptr.hpp>

#include <nebula/define.hpp>

#include <nebula/utilities/types/framework/types.hpp>
#include <nebula/utilities/types/platform/types.hpp>
#include <nebula/utilities/types/content/types.hpp>
#include <nebula/utilities/types/content/universe/types.hpp>
#include <nebula/utilities/types/content/scene/types.hpp>

#include <nebula/ns.hpp>

namespace nebula
{
	namespace content
	{
		class base:
			public jess::enable_shared_from_this<nc::base>
		{
			public:
				/// ctor
				base();
				/// dtor
				virtual ~base();
				/// init
				virtual void							init( jess::shared_ptr<nebula::framework::app> );
				/// shutdown
				virtual void							shutdown();
				/// update
				virtual void							update();
				/// create universe
				template <class T> jess::shared_ptr<T>				create_universe()
				{
					// log
					jess::clog << NEB_FUNCSIG << std::endl;

					jess::shared_ptr<T> t( new T );				

					universes_.push<T>( t );//uni, std::bind( &T::init, std::placeholders::_1, shared_from_this() ) );

					t->init( shared_from_this() );

					return t;
				}
				/// request window
				virtual jess::shared_ptr<npw::base>				request_window();
				/// register universe
				virtual void							register_universe( jess::shared_ptr<ncua::base> );
				/// register scene
				virtual void							register_scene( jess::shared_ptr<nc_sc_a::base> );
				/// physics
				jess::shared_ptr<ncp::base>					physics_;
				/// universes
				jess::map<ncua::base>						universes_;
				/// parent
				std::weak_ptr<nebula::framework::app>				parent_;
		};
	}
}




#endif
