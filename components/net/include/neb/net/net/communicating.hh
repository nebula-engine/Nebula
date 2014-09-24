#ifndef __NEBULA_ASIO_NETWORK_COMMUNICATING_H__
#define __NEBULA_ASIO_NETWORK_COMMUNICATING_H__

#include <neb/util/decl.hpp>

#include <gal/net/communicating.hpp>

namespace neb {
	namespace Network {
		class Communicating:
			virtual public gal::net::communicating
		{
			public:
				Communicating(boost::asio::io_service& io_service, ip::tcp::socket&& socket);
				Communicating(boost::asio::io_service& io_service);
				void			process(std::shared_ptr< gal::net::imessage >);
		};
	}
}

#endif







