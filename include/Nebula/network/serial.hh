#ifndef __GALAXY_NETWORK_SERIAL_H__
#define __GALAXY_NETWORK_SERIAL_H__

#include <assert.h>

#include <galaxy/config.hpp>
#include <galaxy/util.hpp>
#include <galaxy/network/message.hpp>

namespace gal {
        namespace network {
		class base {};
		
        	template<typename DERIVED, typename BASE> class serial: public BASE {
                	public:

				serial() {
				}
				void write(gal::network::message_shared msg) {
					msg->write(this, sizeof(DERIVED));
				}
				void read(gal::network::message_shared msg) {
					msg->read(this, sizeof(DERIVED));
				}
				size_t size() {
					return sizeof(DERIVED);
				}
		};

		template<typename T> class serial2: public T {
			public:
				void write(gal::network::message_shared msg) {

					unsigned char c = T::write_code();

					msg->write(c);

					if(c == 1)
					{
						T::write(msg);
					}
					else if(c == 0)
					{

					}
					else
					{
						printf("invalid write code\n");
						abort();
					}
				}
				void read(gal::network::message_shared msg) {

					unsigned char c;

					msg->read(c);

					if(c == 1)
					{
						T::read(msg);
					}
					else if(c == 0)
					{

					}
					else
					{
						printf("invalid write code\n");
						abort();
					}
				}
				size_t size() {
					return sizeof(T);
				}
		};



		template<typename... Args> class serial_ext {
			public:
				typedef typename gens<sizeof...(Args)>::type seq_type;                  
				typedef std::tuple<std::shared_ptr<Args>...> tuple;

				serial_ext() {
					reset_tuple(tup_);
				}



				template<int i> void read_expand(message_shared msg) {
					auto p = std::get<i>(tup_);

					assert(p);
					//assert(std::get<i>(tup_));

					p->read(msg);
					//std::get<i>(tup_)->read(msg);
				}



				template<int... S> void write_expand(seq<S...>, message_shared msg) {
					pass{(std::get<S>(tup_)->write(msg), 1)...};
				}
				template<int... S> void read_expand(seq<S...>, message_shared msg) {
					//pass{(std::get<S>(tup_)->read(msg), 1)...};
					pass{(read_expand<S>(msg), 1)...};
				}
				template<int... S> size_t size_expand(seq<S...>) {
					size_t size = 0;
					pass{(size += std::get<S>(tup_)->size(), 1)...};
					return size;
				}


				void write(message_shared msg) {
					seq_type s;
					write_expand(s, msg);
				}
				void read(message_shared msg) {
					seq_type s;
					read_expand(s, msg);
				}
				size_t size() {
					seq_type s;
					return size_expand(s);
				}



				tuple tup_;
		};
	}
}

#endif
