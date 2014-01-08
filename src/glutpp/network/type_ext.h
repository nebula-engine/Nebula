#ifndef __NEBULA_NETWORK_TYPE_EXT_H__
#define __NEBULA_NETWORK_TYPE_EXT_H__

namespace glutpp
{
	namespace network
	{
		class type_ext: public gal::network::serializeable
		{
			public:
				type_ext(int type): type_(type) {}
				void write(gal::network::message_shared msg) {
					msg->write(&type_, sizeof(int));
				}
				void read(gal::network::message_shared msg) {
					msg->read(&type_, sizeof(int));
				}
				size_t size() {
					return sizeof(int);
				}

				int type_;
		};
	}
}

#endif



