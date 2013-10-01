#ifndef __NEBULA_CONTENT_VIEW_ADMIN_BASE_HPP__
#define __NEBULA_CONTENT_VIEW_ADMIN_BASE_HPP__

#include <boost/weak_ptr.hpp>


#include <nebula/utilities/types/content/scene/types.hpp>

#include <nebula/ns.hpp>

namespace nebula
{
	namespace content
	{
		namespace view
		{
			namespace admin
			{
				class base
				{
				public:
					base();
					virtual ~base();
					virtual void					init( const boost::shared_ptr<nc_sc_a::base>& );
					virtual void					shutdown();
					virtual void					update();



					boost::weak_ptr<nc_sc_a::base>			parent_;
				};
			}
		}
	}
}

#endif

