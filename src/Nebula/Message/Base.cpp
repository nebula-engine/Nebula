#include <Nebula/Message/Base.hpp>

Neb::Message::Base(gal::network::message_s msg) mag_(msg) {
}

Neb::Message::OBase(): Neb::Message::Base(gal::network::omessage_s(new gal::network::omessage))  {
}

Neb::Message::IBase(): Neb::Message::Base(gal::network::imessage_s(new gal::network::imessage)) {
}

