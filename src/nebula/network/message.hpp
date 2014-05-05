#ifndef __NEBULA_NETWORK_MESSAGE_H__
#define __NEBULA_NETWORK_MESSAGE_H__

#include <nebula/config.hpp>
#include <nebula/control/rigid_body/raw.hpp>

namespace neb {
	namespace network {
		namespace control {
			namespace rigid_body {

				class create {
					public:
						virtual void				serializeDerived(boost::archive::binary_oarchive & ar, unsigned int const & version);
						virtual void				serializeDerived(boost::archive::binary_iarchive & ar, unsigned int const & version);

						glutpp::actor::addr			addr_;
						neb::control::rigid_body::raw		raw_;
				};
				
				class update {
					public:
						glutpp::actor::addr			addr_;
						neb::control::rigid_body::raw		raw_;
				};
			}
		}
	}
}

#endif




