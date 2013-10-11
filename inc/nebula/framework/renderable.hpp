#ifndef __NEBULA_FRAMEWORK_RENDERABLE_HPP__
#define __NEBULA_FRAMEWORK_RENDERABLE_HPP__

#include <boost/chrono.hpp>
#include <boost/asio/high_resolution_timer.hpp>

#include <jess/shared_ptr.hpp>

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
				void						update_fps( boost::system::error_code const & );	
				/// render
				virtual void					render();
				///@name references
				///{
				/// renderer
				jess::shared_ptr<npr::base>			renderer_;
				///}
			protected:
				/// count
				int	count_;
				/// interval
				int	interval_;
				/// fps
				float	fps_;
				/// fps timer
				jess::shared_ptr< boost::asio::basic_waitable_timer<boost::chrono::steady_clock> >	timer_fps_;
		};
	}
}

#endif
