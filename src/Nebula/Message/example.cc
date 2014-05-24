#if 0

void save() {

	Neb::Message::Base_s message(new Neb::Message::Base);

	message->pre();

	// fill message

	message->post();

	Neb::Util::Wrapper<Neb::Message::Base> wrapper(message);

	gal::network::omessage_s buffer(new gal::network::omessage);

	buffer << wrapper;

	// send
}

void load(gal::network::imessage_s buffer) {

	Neb::Util::Wrapper<Neb::Message::Base> wrapper;

	buffer >> wrapper;
	
	wrapper_.ptr_->pre();
	
	wrapper_.ptr_->post();
}

#endif

