#ifndef __NEBULA_NETWORK_MESSAGE_H__
#define __NEBULA_NETWORK_MESSAGE_H__

#include <neb/config.h>
#include <neb/control/rigid_body/raw.h>

namespace neb {
	namespace network {
		namespace control {
			namespace rigid_body {

				typedef gal::network::serial_ext<
					neb::control::rigid_body::raw,
					glutpp::actor::addr>
						ser_create;

				class create: public ser_create {
					public:
						glutpp::actor::addr_s	get_addr() { return std::get<1>(tup_); }
				};

				class update: public ser_create {
					public:
						glutpp::actor::addr_s			get_addr() { return std::get<1>(tup_); }
						neb::control::rigid_body::raw_s		get_raw() { return std::get<0>(tup_); }
				};
			}
		}
	}
}

#endif




