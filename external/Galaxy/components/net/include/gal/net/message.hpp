#ifndef __JESS_ASIO_MESSAGE_HPP__
#define __JESS_ASIO_MESSAGE_HPP__

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sstream>

#include <memory>
#include <deque>

#if defined GAL_NET_USE_BOOST
#include <boost/archive/polymorphic_binary_oarchive.hpp>
#include <boost/archive/polymorphic_binary_iarchive.hpp>

typedef boost::archive::polymorphic_binary_oarchive oarchive;
typedef boost::archive::polymorphic_binary_iarchive iarchive;

#else

#include <gal/net/archive.hpp>

typedef gal::net::oarchive oarchive;
typedef gal::net::iarchive iarchive;

#endif

//namespace sp = std;

#include <gal/net/config.hpp>
#include <gal/net/decl.hpp>

namespace gal {
	namespace net {
		/// message
		class message: public std::enable_shared_from_this<message> {
			public:
				friend class gal::net::communicating;
			public:
				/// ctor
				message();
				virtual ~message() = 0;
				//void				set(void const * const, unsigned int);
				void				reset_head();
				/*void				write(void const * const, size_t);
				template<typename T> void	write(const T& t) {
					write(&t, sizeof(T));
				}*/

				/*template<class T> message&	operator<<(T t) {
				  t.serialize(*this, 0);
				  return *this;
				  }*/


				/*void				read(void * const, size_t);
				template<typename T> void	read(T& t) {
					read(&t, sizeof(T));
				}*/
				
			public: //protected:
				::std::stringstream		ss_;
		};
		class omessage: public message {
			public:
				omessage(): ar_(ss_) {}
				~omessage() {}
				oarchive			ar_;
		};
		class imessage: public message {
			public:
				imessage(): ar_(ss_) {}
				~imessage() {}
				iarchive			ar_;
		};
	}
}














#endif // __JESS_ASIO_MESSAGE_HPP__
