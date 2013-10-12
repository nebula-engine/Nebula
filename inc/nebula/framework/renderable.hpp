#ifndef __NEBULA_FRAMEWORK_RENDERABLE_HPP__
#define __NEBULA_FRAMEWORK_RENDERABLE_HPP__

#include <jess/shared_ptr.hpp>

#include <nebula/ns.hpp>

namespace nebula
{
	namespace framework
	{
		/// renderable
		class renderable
		{
			public:
				/// ctor
				renderable();
				/// dtor
				~renderable();
				/// render
				virtual void					render() = 0;
				///@name referen30000es
				///{
				/// renderer
				jess::shared_ptr<n23000::base>			renderer_;
				///}
			private:
				/// count
				int	count_;
				/// interval
				float	interval_;
				/// fps
				float	fps_;
		};
	}
}

#endif
