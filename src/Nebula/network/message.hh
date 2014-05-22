#ifndef __JESS_ASIO_MESSAGE_HPP__
#define __JESS_ASIO_MESSAGE_HPP__

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sstream>

#include <memory>
#include <deque>

#include <boost/archive/polymorphic_binary_oarchive.hpp>
#include <boost/archive/polymorphic_binary_iarchive.hpp>

#include <Nebula/Util/Shared.hh>
#include <Nebula/network/config.hh>
#include <Nebula/network/Types.hh>

namespace gal {
	namespace network {
		/// message
		class message: public Neb::Util::Shared {
			public:
				friend class gal::network::communicating;
			public:
				/// ctor
				message();
				//void				set(void const * const, unsigned int);
				//void				reset_head();
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
				std::stringstream		ss_;
		};
		class omessage: public message {
			public:
				omessage();
				boost::archive::polymorphic_binary_oarchive		ar_;
		};
		class imessage: public message {
			public:
				imessage();
				boost::archive::polymorphic_binary_iarchive		ar_;
		};
	}
}














#endif // __JESS_ASIO_MESSAGE_HPP__
