#if 0

void save() {

	sp::shared_ptr<neb::Message::Base> message(new neb::Message::Base);

	message->pre();

	// fill message

	message->post();

	neb::Util::Wrapper<neb::Message::Base> wrapper(message);

	sp::shared_ptr<gal::network::omessage> buffer(new gal::network::omessage);

	buffer << wrapper;

	// send
}

void load(sp::shared_ptr<gal::network::imessage> buffer) {

	neb::Util::Wrapper<neb::Message::Base> wrapper;

	buffer >> wrapper;
	
	wrapper_.ptr_->pre();
	
	wrapper_.ptr_->post();
}

#endif

