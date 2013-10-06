#ifndef __NEBULA_CONTENT_VIEW_ADMIN_BASE_HPP__
#define __NEBULA_CONTENT_VIEW_ADMIN_BASE_HPP__

#include <nebula/utilities/types/types.hpp>
#include <nebula/utilities/types/content/scene/types.hpp>
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
					public nf::renderable
				{
				public:
					/// ctor
					base();
					/// dtor
					virtual ~base();
					/// init
					virtual void					init( jess::shared_ptr<nc_sc_a::base>& );
					/// shutdown
					virtual void					shutdown();
					/// update
					virtual void					update();
					/// render
					virtual void					render();
					/// create camera
					virtual void					create_camera();
					/// parent
					std::weak_ptr<nc_sc_a::base>			parent_;
					///@name references
					///{
					/// window
					jess::shared_ptr<npw::base>			window_;
					/// camera
					jess::shared_ptr<n0x30000::camera>		camera_;
					///}

				};
			}
		}
	}
}

#endif

