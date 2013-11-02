#ifndef __NEBULA_CONTENT_VIEW_ADMIN_BASE_HPP__
#define __NEBULA_CONTENT_VIEW_ADMIN_BASE_HPP__

#include <nebula/framework/renderable.hpp>
#include <nebula/ns.hpp>

namespace nebula
{
	namespace content
	{
		namespace view
		{
			namespace admin
			{
				/// base
				class base:
					public n10000::renderable
				{
				public:
					/// ctor
					base();
					/// dtor
					virtual ~base();
					/// init
					virtual void					init( std::shared_ptr<n32100::base> );
					/// shutdown
					virtual void					shutdown();
					/// update
					virtual void					update();
					/// render
					virtual void					render();
					/// create camera
					virtual void					create_camera();
					/// parent
					std::weak_ptr<n32100::base>			parent_;
					///@name referen30000es
					///{
					/// window
					std::shared_ptr<n22000::base>			window_;
					/// camera
					std::shared_ptr<n30000::camera>			camera_;
					/// ui
					std::shared_ptr<n51000::base>			layout_;
					///}

				};
			}
		}
	}
}

#endif

