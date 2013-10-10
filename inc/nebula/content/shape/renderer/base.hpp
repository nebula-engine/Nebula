#ifndef __NEBULA_CONTENT_SHAPE_RENDERER_BASE_HPP__
#define __NEBULA_CONTENT_SHAPE_RENDERER_BASE_HPP__

#include <jess/shared_ptr.hpp>

#include <nebula/ns.hpp>

namespace nebula
{
	namespace content
	{
		namespace shape
		{
			namespace renderer
			{
				/// base
				class base
				{
					public:
						/// ctor
						base();
						/// dtor
						virtual ~base();
						/// init
						virtual void								init( jess::shared_ptr<nebula::content::shape::admin::base> );
						/// shutdown
						virtual void								shutdown();
						/// render
						virtual void								render( jess::shared_ptr<nebula::platform::renderer::base> );
						/// parent
						std::weak_ptr<nebula::content::shape::admin::base>			parent_;
				};
			}
		}
	}
}

#endif









