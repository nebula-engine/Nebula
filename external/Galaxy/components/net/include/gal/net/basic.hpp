#ifndef __JESS_ASIO_NETWORK_SOCKET_BASIC_HPP__
#define __JESS_ASIO_NETWORK_SOCKET_BASIC_HPP__

#include <mutex>
#include <condition_variable>

namespace gal {
	namespace net {
		/** %socket %communicating
		 */
		class __basic {
			public:
				enum {
					TERMINATE = 1 << 0,
					ERROR = 1 << 1
				};
			protected:
				__basic();
				//void					notify_bits(unsigned int bits);

				//unsigned int				bits_;
				//::std::condition_variable		cv_;
				//::std::mutex				mutex_;
		};
	}
}




#endif





