#ifndef __NEBULA_FRAMEWORK_APP_HPP__
#define __NEBULA_FRAMEWORK_APP_HPP__

#include <memory>

#include <ker/module/module.hpp>

#include <nebula/ns.hpp>

namespace nebula
{
	namespace framework
	{
		/// %app
		class app:
			public ker::module::module
		{
		public:
			/// ctor
			app();
			/// dtor
			virtual ~app();
			/// init
			void							init();
			/// shutdown
			virtual void						shutdown();
			void							main_loop();
			/// main loop sequ
			void							MainLoopSequ();
			/// main loop multi
			void							MainLoopMulti();
			/// continue sequ
			void							ContinueLoopSequ();
			/// continue multi
			void							ContinueLoopMulti();
			/// request_window
			//virtual std::shared_ptr<n22000::base>			request_window();
			/// get content
			//std::shared_ptr<n30000::base>				get_content();
			/// get platform
			//std::shared_ptr<n21000::base>				get_platform();
			///@name children
			///@{
			/// contnt
			std::shared_ptr<n30000::base>				content_;
			/// platform
			std::shared_ptr<n21000::base>				platform_;
			/// renderable
			std::shared_ptr<n10000::renderable>			renderable_;
			///@}

		};
	}
}

#endif

