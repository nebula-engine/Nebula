#ifndef NEBULA_NETWORK_TYPES_HPP
#define NEBULA_NETWORK_TYPES_HPP

namespace gal {
	namespace network {
		class communicating;

		class message;
		class omessage;
		class imessage;



		typedef boost::shared_ptr<message>	message_s;
		typedef boost::shared_ptr<omessage>	omessage_s;
		typedef boost::shared_ptr<imessage>	imessage_s;

	}
}

#endif
