#ifndef __NEBULA_CONTENT_UNIVERSE_ADMIN_BASE_HPP__
#define __NEBULA_CONTENT_UNIVERSE_ADMIN_BASE_HPP__

#include <boost/bind.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include <jess/shared_ptr.hpp>
#include <jess/ostream.hpp>
#include <jess/map.hpp>

#include <nebula/define.hpp>
#include <nebula/utilities/types/platform/types.hpp>
#include <nebula/utilities/types/content/types.hpp>
#include <nebula/utilities/types/content/scene/types.hpp>

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
					public boost::enable_shared_from_this<ncua::base>
				{
				public:
					/// ctor
					base();
					/// dtor
					virtual ~base();
					/// init
					virtual void						init(const boost::shared_ptr<nebula::content::base>&);
					/// shutdown
					virtual void						shutdown();
					/// update
					virtual void						update();
					/// request window
					virtual void						request_window( jess::shared_ptr<npw::base>& wnd );
					/// create scene
					template <class T> void					create_scene( boost::shared_ptr<T>& scn )
					{
						jess::clog << NEB_FUNCSIG << std::endl;
	
						scenes_.push<T>( scn, boost::bind( &T::init, _1, shared_from_this() ) );

					}
					
					/// parent
					boost::weak_ptr<nebula::content::base>			parent_;
					
					/// scenes
					jess::map<nc_sc_a::base>				scenes_;
				};
			}
		}
	}
}




#endif
