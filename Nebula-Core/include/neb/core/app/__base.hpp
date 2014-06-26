#ifndef __NEBULA_APP___BASE_H__
#define __NEBULA_APP___BASE_H__

#include <boost/asio/io_service.hpp>

#include <neb/core/app/util/Flag.hh>

namespace neb {
	namespace app {
		/** @brief %base */
		class __base {
			public:
				virtual void					init();

				boost::asio::io_service				ios_;

				neb::app::util::flag				flag_;


			public:
				static ::std::shared_ptr<neb::app::__base>	g_app_;
		};
	}
}

#endif



