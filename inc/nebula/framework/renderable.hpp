#ifndef __NEBULA_FRAMEWORK_RENDERABLE_HPP__
#define __NEBULA_FRAMEWORK_RENDERABLE_HPP__

#include <thread>
#include <memory>


#include <nebula/ns.hpp>

namespace nebula
{
	namespace framework
	{
		/// renderable
		class renderable:
			public std::enable_shared_from_this<n10000::renderable>
		{
			public:
				/// ctor
				renderable();
				/// dtor
				~renderable();
				/// init
				virtual void					init();
				/// update fps
				void						update_fps();	
				/// render
				virtual void					render();
				///@name references
				///{
				/// renderer
				std::shared_ptr<n23000::base>			renderer_;
				///}
			protected:
				/// count
				int	count_;
				/// total count
				int	total_count_;
				/// interval
				int	interval_;
				/// fps
				int	fps_;
				/// clock
				int	clock_;
				/// fps timer
				std::thread					timer_fps_;
				/** \brief mutex
				*/
				std::mutex mutex_;
		};
	}
}

#endif
