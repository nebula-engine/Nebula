#ifndef __NEBULA_CONTENT_UNIVERSE_ADMIN_BASE_HPP__
#define __NEBULA_CONTENT_UNIVERSE_ADMIN_BASE_HPP__

#include <jess/shared_ptr.hpp>
#include <jess/ostream.hpp>
#include <jess/map.hpp>

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
					public jess::enable_shared_from_this<ncua::base>
				{
					public:
						/// ctor
						base();
						/// dtor
						virtual ~base();
						/// init
						virtual void						init( jess::shared_ptr<nebula::content::base> );
						/// shutdown
						virtual void						shutdown();
						/// update
						virtual void						update();
						/// request window
						virtual jess::shared_ptr<npw::base>			request_window();
						/// create scene
						template <class T> jess::shared_ptr<T>			create_scene()
						{
							jess::clog << NEB_FUNCSIG << std::endl;

							jess::shared_ptr<T> t( new T );

							scenes_.push<T>( t );//, std::bind( &T::init, std::placeholders::_1, shared_from_this() ) );

							t->init( shared_from_this() );

							return t;
						}

						/// parent
						std::weak_ptr<nebula::content::base>			parent_;

						/// scenes
						jess::map<nc_sc_a::base>				scenes_;
				};
			}
		}
	}
}




#endif
