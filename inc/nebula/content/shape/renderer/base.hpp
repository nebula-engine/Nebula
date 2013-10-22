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
						base( jess::shared_ptr<n35100::base> );
						/// dtor
						virtual ~base();
						/// init
						virtual void								init();
						/// shutdown
						virtual void								shutdown();
						/// render
						virtual void								render( jess::shared_ptr<n23000::base> );
						/// parent
						std::weak_ptr<n35100::base>			parent_;
				};
			}
		}
	}
}

#endif









