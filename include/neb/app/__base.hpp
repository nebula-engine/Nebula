#ifndef __NEBULA_APP___BASE_H__
#define __NEBULA_APP___BASE_H__

#include <boost/asio/io_service.hpp>

#include <neb/app/Util/Flag.hh>

namespace neb {
	namespace app {
		/** @brief %base */
		class __base {
			public:
				virtual void					init();

				boost::asio::io_service				ios_;

				neb::app::util::flag				flag_;
		};
	}
}

#endif



