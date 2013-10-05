#ifndef __NEBULA_FRAMEWORK_RENDERABLE_HPP__
#define __NEBULA_FRAMEWORK_RENDERABLE_HPP__

#include <boost/shared_ptr.hpp>

#include <nebula/utilities/types/platform/types.hpp>
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
			///@name sideways
			///{
			/// renderer
			boost::shared_ptr<npr::base>			renderer_;
			///}
		};
	}
}

#endif
