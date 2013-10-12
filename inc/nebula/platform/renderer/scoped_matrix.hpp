#ifndef __NEBULA_PLATFORM_RENDERER_SCOPED_MATRIX_HPP__
#define __NEBULA_PLATFORM_RENDERER_SCOPED_MATRIX_HPP__

#include <nebula/platform/renderer/base.hpp>

namespace nebula
{
	namespace platform
	{
		namespace renderer
		{
			struct scoped_matrix
			{
				public:
					scoped_matrix( jess::shared_ptr<n23000::base> renderer ): renderer_(renderer)
				{
					renderer_->push_matrix();
				}
					~scoped_matrix()
					{
						renderer_->pop_matrix();
					}
				private:
					scoped_matrix();
					jess::shared_ptr<n23000::base>	renderer_;
			};
		}
	}
}
#endif
