#ifndef __NEBULA_FRAMEWORK_RENDERABLE_HPP__
#define __NEBULA_FRAMEWORK_RENDERABLE_HPP__

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
			virtual void					render();
			///@name sideways
			///{
			/// renderer
			boost::shared_ptr<npr::base>			renderer_;
			///}
		};
	}
}

#endif
