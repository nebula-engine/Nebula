#if 0

void save() {

	std::shared_ptr<neb::message::base> message(new neb::message::base);

	message->pre();

	// fill message

	message->post();

	neb::util::Wrapper<neb::message::base> wrapper(message);

	std::shared_ptr<gal::network::omessage> buffer(new gal::network::omessage);

	buffer << wrapper;

	// send
}

void load(std::shared_ptr<gal::network::imessage> buffer) {

	neb::util::Wrapper<neb::message::base> wrapper;

	buffer >> wrapper;
	
	wrapper_.ptr_->pre();
	
	wrapper_.ptr_->post();
}

#endif

