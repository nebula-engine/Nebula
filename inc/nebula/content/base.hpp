#ifndef __NEBULA_CONTENT_BASE_HPP__
#define __NEBULA_CONTENT_BASE_HPP__

#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>

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
			public boost::enable_shared_from_this<nc::base>
		{
		public:
			/// ctor
			base();
			/// dtor
			virtual ~base();
			/// init
			virtual void							init(const boost::shared_ptr<nebula::framework::app>&);
			/// shutdown
			virtual void							shutdown();
			/// update
			virtual void							update();
			/// create universe
			template <class T> void						create_universe( boost::shared_ptr<T>& uni )
			{
				// log
				jess::clog << NEB_FUNCSIG << std::endl;
				
				universes_.push<T>( uni, boost::bind( &T::init, _1, shared_from_this() ) );
			}
			/// request window
			virtual void							request_window( jess::shared_ptr<npw::base>& );
			/// register universe
			virtual void							register_universe( boost::shared_ptr<ncua::base> );
			/// register scene
			virtual void							register_scene( boost::shared_ptr<nc_sc_a::base> );
			/// physics
			jess::shared_ptr<ncp::base>					physics_;
			/// universes
			jess::map<ncua::base>						universes_;
			/// parent
			boost::weak_ptr<nebula::framework::app>				parent_;
		};
	}
}




#endif
