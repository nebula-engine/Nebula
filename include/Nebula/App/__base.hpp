#ifndef __NEBULA_APP___BASE_H__
#define __NEBULA_APP___BASE_H__

#include <boost/asio/io_service.hpp>

namespace neb {
	namespace App {
		class __base {
			public:
				virtual void					init();

				boost::asio::io_service				ios_;

		};
	}
}

#endif



