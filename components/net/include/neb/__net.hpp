#ifndef __NEBULA_APP___NET_H__
#define __NEBULA_APP___NET_H__

#include <fstream>

#include <boost/archive/polymorphic_xml_iarchive.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <gal/itf/shared.hpp>

#include <gal/net/decl.hpp>

#include <neb/app/__base.hpp>
#include <neb/net/server.hh>
#include <neb/net/client.hh>
#include <neb/message/Types.hh>

namespace neb {
	namespace app {


		class __net:
			virtual public neb::app::__base
		{
			public:
				void					reset_server(ip::tcp::endpoint const & endpoint);
				void					reset_client(ip::tcp::resolver::iterator endpoint_iterator);

				void					sendServer(std::shared_ptr< gal::net::omessage >);
				void					sendServer(std::shared_ptr< neb::message::OBase > message);
				void					sendClient(std::shared_ptr< gal::net::omessage >);
				void					sendClient(std::shared_ptr< neb::message::OBase > message);


				std::shared_ptr<neb::Network::Server>				server_;
				std::shared_ptr<neb::Network::Client>				client_;

		};

	}
}
#endif





