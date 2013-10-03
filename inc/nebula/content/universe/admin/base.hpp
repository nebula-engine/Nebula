#ifndef __NEBULA_CONTENT_UNIVERSE_ADMIN_BASE_HPP__
#define __NEBULA_CONTENT_UNIVERSE_ADMIN_BASE_HPP__

#include <boost/weak_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include <jess/map.hpp>

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

					/// scene
					virtual void						create_scene( boost::shared_ptr<nc_sc_a::base>& );

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
