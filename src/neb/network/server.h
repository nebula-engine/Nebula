#ifndef __NEBULA_NETWORK_SERVER_H__
#define __NEBULA_NETWORK_SERVER_H__

#include <gal/network/server.h>

#include <neb/network/communicating.h>

namespace neb
{
        namespace network
        {
                typedef gal::network::server<neb::network::communicating> server;

        }
}

#endif

