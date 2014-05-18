#ifndef NEBULA_MESSAGE_BASE_HPP
#define NEBULA_MESSAGE_BASE_HPP

#include <Nebula/network/message.hh>

#include <Nebula/Message/Types.hh>

namespace Neb {
	namespace Message {
		class Base {
			public:
				template<class D, class... A> static Neb::Message::Base_s	alloc(A... a) {
					Neb::Message::Base_s d(new D(a...));
					d->pre();
					return d;
				}
			protected:
				Base();
				virtual void			pre() {}
				virtual void			post() {}
			public:
				/** @brief get message for writing.
				 * This will lose ownership of @c msg_
				 */
				virtual gal::network::message_s &	getMessageForWriting() = 0;
			protected:

		};
		class OBase: public Base {
			public:
				OBase();

				
				gal::network::omessage_s	msg_;
		};
		class IBase: public Base {
			public:
				IBase();

				/** @brief process.
				 * called after message is deserialized
				 */
				virtual void			process() = 0;

				gal::network::imessage_s	msg_;
		};
	}
}

#endif
