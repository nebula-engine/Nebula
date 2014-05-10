#ifndef NEBULA_MESSAGE_BASE_HPP
#define NEBULA_MESSAGE_BASE_HPP

namespace Neb {
	namespace Message {
		class Base {
			public:
				template<class D, class... A>
				static Neb::Message::Base_s	alloc(A... a) {
					Neb::Message::Base_s d(new D(a...));
					d->pre();
					return d;
				}
			private:
				Base();
				virtual void			pre() {}
				virtual void			post() {}
			public:
				/** @brief get message for writing.
				 * This will lose ownership of @c msg_
				 */
				gal::network::message_s &	getMessageForWriting() {
					return msg_;
				}
			protected:
				gal::network::message_s		msg_;
		};
		class OBase: public Base {
			public:
				OBase();
		};
		class IBase: public Base {
			public:
				IBase();
		};
	}
}

#endif
